/*
  ==============================================================================

    MasterComponent.h
    Created: 28 May 2021 1:45:37pm
    Author:  Zombori Márk

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class MasterComboBoxLookAndFeel : public juce::LookAndFeel_V4
{
public:
    MasterComboBoxLookAndFeel()
    {
        setColour(juce::ComboBox::backgroundColourId, juce::Colours::transparentWhite);
        setColour(juce::ComboBox::arrowColourId, juce::Colours::transparentWhite);
    }
};


class MasterSliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    MasterSliderLookAndFeel()
    {
        setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::white);
        setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::transparentWhite);
        setColour(juce::Slider::thumbColourId, juce::Colours::black);
    }
};

class MasterComponent  : public juce::Component
{
public:
    MasterComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String masterId, juce::String MorGSelectorID, juce::String HorRSelectorID);
    ~MasterComponent() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    juce::Slider masterSlider;
    juce::Label masterLabel {"Master", "Master"};
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterAttachment;
    juce::Slider glideSlider;
    juce::Label glideLabel {"Glider", "Glider"};
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> glideAttachment;
    juce::String componentName {""};
    juce::ComboBox MorGBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> MorGAttachment;
    
    
    MasterSliderLookAndFeel sliderLookAndFeel;
    MasterComboBoxLookAndFeel comboBoxLookAndFeel;
};
