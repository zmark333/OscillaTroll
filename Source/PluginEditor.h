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

class EditorComboBoxLookAndFeel : public juce::LookAndFeel_V4
{
public:
    EditorComboBoxLookAndFeel()
    {
        setColour(juce::ComboBox::backgroundColourId, juce::Colours::transparentWhite);
        setColour(juce::ComboBox::arrowColourId, juce::Colours::transparentWhite);
    }
};


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
    
    juce::ImageComponent mImageComponent;
    juce::ImageComponent mImageComponent2;
    
    juce::ComboBox HorRBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> HorRAttachment;

    EditorComboBoxLookAndFeel lookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillaTroll02AudioProcessorEditor)
};
