/*
  ==============================================================================

    OscData.h
    Created: 2 May 2021 2:17:40pm
    Author:  Zombori Márk

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType(const int choice);
    void setWaveFrequency (const int midiNoteNumber);
    void getNewAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setFmParams (const float depth, const float freq);
    void setGain(const float levelInDecibels);
    void setPitch(const int pitch);
    
    
private:
    juce::dsp::Oscillator<float> fmOsc {[](float x) {return std::sin(x); }};
    int lastPitch { 0 };
    float fmMod {0.0f};
    float fmDepth {0.0f};
    int lastMidiNote {0};
    juce::dsp::Gain<float> gain;
    
    
};
