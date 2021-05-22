/*
  ==============================================================================

    OscData.cpp
    Created: 2 May 2021 2:17:40pm
    Author:  Zombori Márk

  ==============================================================================
*/

#include "OscData.h"

void OscData:: prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    fmOsc.prepare(spec);
    lfoOsc.prepare(spec);
    prepare(spec);
    gain.prepare(spec);
    sampleRateUse=spec.sampleRate;
    
}

void OscData::setWaveType(const int choice)
{
    
    switch (choice) {
        case 0:
            // sine wave
            initialise([](float x) {return std::sin(x); });
            break;
            
        case 1:
            // saw wave
            initialise([](float x) {return x/ juce::MathConstants<float>::pi; });
            break;
            
        case 2:
            // square wave
            initialise([](float x) {return x<0.0f ? -1.0f :1.0f; });
            break;
            
        default:
            jassertfalse;
            break;
    }
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber+lastPitch)+fmMod);
    lastMidiNote=midiNoteNumber;
}

void OscData::getNewAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    for (int ch=0; ch<block.getNumChannels(); ch++)
    {
        for(int s=0; s<block.getNumSamples(); s++)
        {
            fmMod=fmOsc.processSample(block.getSample(ch, s))*fmDepth;
            //lfoMod=lfoOsc.processSample(block.getSample(ch, s))*lfoDepth;
        }
    }
    
    process(juce::dsp::ProcessContextReplacing<float> (block));
    gain.process (juce::dsp::ProcessContextReplacing<float> (block));
}

void OscData::setFmParams(const float depth, const float freq)
{
    fmOsc.setFrequency(freq);
    fmDepth=depth;
    //auto currentFreq=juce::MidiMessage::getMidiNoteInHertz(lastMidiNote)+fmMod;
    //setFrequency(currentFreq>=0 ? currentFreq: currentFreq* -1.0f);
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote+lastPitch)+fmMod);
}

void OscData::setLfoParams(const float depth, const float freq)
{
    lfoOsc.setFrequency(freq*48);
    lfoDepth=depth;
}

void OscData::setGain(const float levelInDecibels)
{
    //juce::dsp::decibelsToGain<float>(levelInDecibels);
    gain.setGainDecibels(levelInDecibels+lfoMod);
}

void OscData::setPitch(const int pitch)
{
    lastPitch=pitch;
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote+lastPitch)+fmMod);
}

float OscData::processNextSample (float input)
{
    //input=0;
    fmMod = fmOsc.processSample (input) * fmDepth;
    if (counter==48)
    {
        lfoMod = lfoOsc.processSample (input) * lfoDepth;
        counter=0;
    }
    counter++;
    lastProcessSample=gain.processSample (processSample (input));
    //std::cout<<input<<std::endl;
    //std::cout<<gain.processSample (processSample (input))<<std::endl;
    return gain.processSample (processSample (input));
}
