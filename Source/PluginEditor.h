/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "AdsrComponent.h"
#include "OscComponent.h"
#include "MasterComponent.h"


//==============================================================================
/**
*/
class OscillaTroll02AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    OscillaTroll02AudioProcessorEditor (OscillaTroll02AudioProcessor&);
    ~OscillaTroll02AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void HorR (bool isHertz);
    
private:
    OscillaTroll02AudioProcessor& audioProcessor;
    OscComponent osc1;
    OscComponent osc2;
    OscComponent osc3;
    OscComponent osc4;
    OscComponent osc5;
    OscComponent osc6;
    OscComponent osc7;
    OscComponent osc8;
    OscComponent osc9;
    OscComponent osc10;
    AdsrComponent adsr;
    MasterComponent master;
    
    juce::ComboBox HorRBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> HorRAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillaTroll02AudioProcessorEditor)
};
