/*
  ==============================================================================

    MasterComponent.h
    Created: 28 May 2021 1:45:37pm
    Author:  Zombori Márk

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class MasterSliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    MasterSliderLookAndFeel()
    {
        setColour(juce::Slider::backgroundColourId, juce::Colours::royalblue);
        setColour(juce::Slider::trackColourId, juce::Colours::lightsteelblue);
        setColour(juce::Slider::thumbColourId, juce::Colours::navy);
    }
};

class MasterComponent  : public juce::Component
{
public:
    MasterComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String masterId);
    ~MasterComponent() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    juce::Slider masterSlider;
    juce::Label masterLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterAttachment;
    juce::Slider glideSlider;
    juce::Label glideLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> glideAttachment;
    juce::String componentName {""};
    
    MasterSliderLookAndFeel sliderLookAndFeel;
};
