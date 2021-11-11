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
    void setMasterVolume(const float vol) {masterVolume=vol;}
    
    
    std::array<OscData, 2>& getOscillator1() { return osc1; }
    std::array<OscData, 2>& getOscillator2() { return osc2; }
    std::array<OscData, 2>& getOscillator3() { return osc3; }
    std::array<OscData, 2>& getOscillator4() { return osc4; }
    std::array<OscData, 2>& getOscillator5() { return osc5; }
    std::array<OscData, 2>& getOscillator6() { return osc6; }
    std::array<OscData, 2>& getOscillator7() { return osc7; }
    std::array<OscData, 2>& getOscillator8() { return osc8; }
    std::array<OscData, 2>& getOscillator9() { return osc9; }
    std::array<OscData, 2>& getOscillator10() { return osc10; }
    
private:
    juce::AudioBuffer<float> synthBuffer;
    
    float masterVolume;
    
    std::array<OscData, 2> osc1;
    std::array<OscData, 2> osc2;
    std::array<OscData, 2> osc3;
    std::array<OscData, 2> osc4;
    std::array<OscData, 2> osc5;
    std::array<OscData, 2> osc6;
    std::array<OscData, 2> osc7;
    std::array<OscData, 2> osc8;
    std::array<OscData, 2> osc9;
    std::array<OscData, 2> osc10;
    /*OscData osc1;
    OscData osc2;
    OscData osc3;
    OscData osc4;
    OscData osc5;
    OscData osc6;
    OscData osc7;
    OscData osc8;
    OscData osc9;
    OscData osc10;
     */
    AdsrData adsr;
    
    juce::dsp::Gain<float> gain;
    
    bool isPrepared{false};
};
