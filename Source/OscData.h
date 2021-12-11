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
    void setLfoParams (const float depth, const float freq);
    void setGain(const float levelInDecibels);
    void setPitch(const int pitch);
    void setDetuner(const float detune);
    void setGlide(const int glide);
    void gliding();
    float processNextSample (float input);
    
    
private:
    juce::dsp::Oscillator<float> fmOsc {[](float x) {return std::sin(x); }};
    juce::dsp::Oscillator<float> lfoOsc {[](float x) {return x<0.0f ? -1.0f :1.0f; }};
    int lastPitch { 0 };
    float fmMod {0.0f};
    float fmDepth {0.0f};
    float lfoMod {0.0f};
    float lfoDepth {10.0f};
    float detuner {0.0f};
    int lastMidiNote {0};
    int counter {0};
    double sampleRateUse;
    juce::dsp::Gain<float> gain;
    float lastProcessSample;
    
    bool isGlide;
    int glider;
    int glideLastMidiNote;
    int glideCounter;
    bool glideHappening;
    int fromGlideMidiNote;
    float helper{220.0f};
    
    
    
};
