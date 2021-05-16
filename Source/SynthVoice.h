/*
  ==============================================================================

    SynthVoice.h
    Created: 2 May 2021 2:16:19pm
    Author:  Zombori Márk

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "AdsrData.h"
#include "OscData.h"

class SynthVoice: public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber,float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    //bool isVoiceActive() const;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    //void aftertouchChanged (int newAftertouchValue);
    //void channelPressureChanged (int newChannelPressureValue);
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    void updateAdsr(const float attack, const float decay, const float sustain, const float release);
    
    
    OscData& getOscillator1() { return osc1; }
    OscData& getOscillator2() { return osc2; }
    
private:
    juce::AudioBuffer<float> synthBuffer;
    
    OscData osc1;
    OscData osc2;
    AdsrData adsr;
    
    juce::dsp::Gain<float> gain;
    
    bool isPrepared{false};
};
