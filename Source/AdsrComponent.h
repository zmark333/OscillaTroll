/*
  ==============================================================================

    AdsrComponent.h
    Created: 2 May 2021 2:18:33pm
    Author:  Zombori Márk

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
 */

class ADSRSliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    ADSRSliderLookAndFeel()
    {
        setColour(juce::Slider::backgroundColourId, juce::Colours::lightsteelblue);
        setColour(juce::Slider::trackColourId, juce::Colours::royalblue);
        setColour(juce::Slider::thumbColourId, juce::Colours::navy);
    }
};


class AdsrComponent  : public juce::Component
{
public:
    AdsrComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId);
    ~AdsrComponent() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    void setSliderParams(juce::Slider& slider);
    
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    //juce::ComboBox oscSelector;
    
    juce::Label attackLabel {"A", "A"};
    juce::Label decayLabel {"D", "D"};
    juce::Label sustainLabel {"S", "S"};
    juce::Label releaseLabel {"R", "R"};
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    
    juce::String componentName {""};
    
    ADSRSliderLookAndFeel sliderLookAndFeel;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
