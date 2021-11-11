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
    for (int i = 0; i < 2; i++)
    {
        osc1[i].setWaveFrequency(midiNoteNumber);
        osc2[i].setWaveFrequency(midiNoteNumber);
        osc3[i].setWaveFrequency(midiNoteNumber);
        osc4[i].setWaveFrequency(midiNoteNumber);
        osc5[i].setWaveFrequency(midiNoteNumber);
        osc6[i].setWaveFrequency(midiNoteNumber);
        osc7[i].setWaveFrequency(midiNoteNumber);
        osc8[i].setWaveFrequency(midiNoteNumber);
        osc9[i].setWaveFrequency(midiNoteNumber);
        osc10[i].setWaveFrequency(midiNoteNumber);
    }
    
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
    
    for (int i = 0; i < 2; i++)
    {
        osc1[i].prepareToPlay(spec);
        osc2[i].prepareToPlay(spec);
        osc3[i].prepareToPlay(spec);
        osc4[i].prepareToPlay(spec);
        osc5[i].prepareToPlay(spec);
        osc6[i].prepareToPlay(spec);
        osc7[i].prepareToPlay(spec);
        osc8[i].prepareToPlay(spec);
        osc9[i].prepareToPlay(spec);
        osc10[i].prepareToPlay(spec);
        adsr.setSampleRate(sampleRate);
    }
    
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
    
    /*osc1.getNewAudioBlock(audioBlock);
    osc2.getNewAudioBlock(audioBlock);
    osc3.getNewAudioBlock(audioBlock);
    osc4.getNewAudioBlock(audioBlock);
    osc5.getNewAudioBlock(audioBlock);
    osc6.getNewAudioBlock(audioBlock);
    osc7.getNewAudioBlock(audioBlock);
    osc8.getNewAudioBlock(audioBlock);
    osc9.getNewAudioBlock(audioBlock);
    osc10.getNewAudioBlock(audioBlock);
    */
    
    for (int i = 0; i < synthBuffer.getNumChannels(); ++i)
    {
        auto* buffer = synthBuffer.getWritePointer (i, 0);
        
        for (int j = 0; j < synthBuffer.getNumSamples(); ++j)
        {
            buffer[j] = osc1[i].processNextSample (buffer[j]) + osc2[i].processNextSample (buffer[j]) + osc3[i].processNextSample (buffer[j]) + osc4[i].processNextSample (buffer[j]) + osc5[i].processNextSample (buffer[j]) + osc6[i].processNextSample (buffer[j]) + osc7[i].processNextSample (buffer[j]) + osc8[i].processNextSample (buffer[j]) + osc9[i].processNextSample (buffer[j]) + osc10[i].processNextSample (buffer[j]);
            buffer[j]=buffer[j]*(pow(10, masterVolume/20));
        }
    }
    
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    gain.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    
    for (int channel=0; channel<outputBuffer.getNumChannels();channel++)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        if (!adsr.isActive()) clearCurrentNote();
    }
    
    
}



