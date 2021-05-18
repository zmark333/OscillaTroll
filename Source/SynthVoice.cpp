/*
  ==============================================================================

    SynthVoice.cpp
    Created: 2 May 2021 2:16:19pm
    Author:  Zombori Márk

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}
void SynthVoice::startNote (int midiNoteNumber,float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc1.setWaveFrequency(midiNoteNumber);
    osc2.setWaveFrequency(midiNoteNumber);
    osc3.setWaveFrequency(midiNoteNumber);
    osc4.setWaveFrequency(midiNoteNumber);
    osc5.setWaveFrequency(midiNoteNumber);
    osc6.setWaveFrequency(midiNoteNumber);
    osc7.setWaveFrequency(midiNoteNumber);
    osc8.setWaveFrequency(midiNoteNumber);
    osc9.setWaveFrequency(midiNoteNumber);
    osc10.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
}
void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
    if(!allowTailOff || !adsr.isActive()) clearCurrentNote();
}
void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}
void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    adsr.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    osc1.prepareToPlay(spec);
    osc2.prepareToPlay(spec);
    osc3.prepareToPlay(spec);
    osc4.prepareToPlay(spec);
    osc5.prepareToPlay(spec);
    osc6.prepareToPlay(spec);
    osc7.prepareToPlay(spec);
    osc8.prepareToPlay(spec);
    osc9.prepareToPlay(spec);
    osc10.prepareToPlay(spec);
    adsr.setSampleRate(sampleRate);
    
    gain.prepare(spec);
    gain.setGainLinear(0.07f);
    
    isPrepared=true;
}

void SynthVoice::updateAdsr(const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}


void SynthVoice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
    
    if (! isVoiceActive()) return;
    
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    
    juce::dsp::AudioBlock<float> audioBlock {synthBuffer};
    osc1.getNewAudioBlock(audioBlock);
    osc2.getNewAudioBlock(audioBlock);
    osc3.getNewAudioBlock(audioBlock);
    osc4.getNewAudioBlock(audioBlock);
    osc5.getNewAudioBlock(audioBlock);
    osc6.getNewAudioBlock(audioBlock);
    osc7.getNewAudioBlock(audioBlock);
    osc8.getNewAudioBlock(audioBlock);
    osc9.getNewAudioBlock(audioBlock);
    osc10.getNewAudioBlock(audioBlock);
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    gain.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    
    for (int channel=0; channel<outputBuffer.getNumChannels();channel++)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        if (!adsr.isActive()) clearCurrentNote();
    }
    
    
}



