/*
  ==============================================================================

    OscComponent.h
    Created: 2 May 2021 2:18:18pm
    Author:  Zombori Márk

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//==============================================================================
/*
 */

class ComboBoxLookAndFeel : public juce::LookAndFeel_V4
{
public:
    ComboBoxLookAndFeel()
    {
        setColour(juce::ComboBox::backgroundColourId, juce::Colours::steelblue);
        setColour(juce::ComboBox::arrowColourId, juce::Colours::steelblue);
    }
};

class SliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    SliderLookAndFeel()
    {
        setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::royalblue);
        setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::lightsteelblue);
        setColour(juce::Slider::thumbColourId, juce::Colours::navy);
    }
};

class OtherSliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    OtherSliderLookAndFeel()
    {
        setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::lightsteelblue);
        setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::lightsteelblue);
        setColour(juce::Slider::thumbColourId, juce::Colours::navy);
    }
};


class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String name, juce::String waveSelectorID, juce::String fmFreqId, juce::String fmDepthId, juce::String gainId, juce::String pitchId, juce::String lfoFreqId, juce::String lfoDepthId, juce::String detunerId);
    ~OscComponent() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    juce::ComboBox oscWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;
    
    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
    juce::Slider lfoFreqSlider;
    juce::Slider lfoDepthSlider;
    juce::Slider gainSlider;
    juce::Slider pitchSlider;
    juce::Slider detunerSlider;
    
    using Attachment=juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<Attachment> fmFreqAttachment;
    std::unique_ptr<Attachment> fmDepthAttachment;
    std::unique_ptr<Attachment> lfoFreqAttachment;
    std::unique_ptr<Attachment> lfoDepthAttachment;
    std::unique_ptr<Attachment> gainAttachment;
    std::unique_ptr<Attachment> pitchAttachment;
    std::unique_ptr<Attachment> detunerAttachment;
    
    juce::Label fmFreqLabel{"FM Freq", "FM Freq"};
    juce::Label fmDepthLabel{"FM Depth", "FM Depth"};
    juce::Label lfoFreqLabel{"LFO Freq", "LFO Freq"};
    juce::Label lfoDepthLabel{"LFO Depth", "LFO Depth"};
    juce::Label gainLabel{"Gain", "Gain"};
    juce::Label pitchLabel{"Pitch", "Pitch"};
    juce::Label detunerLabel{"Detune", "Detune"};
    
    juce::String componentName {""};
    
    ComboBoxLookAndFeel comboBoxLookAndFeel;
    SliderLookAndFeel sliderLookAndFeel;
    OtherSliderLookAndFeel otherSliderLookAndFeel;
  
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};


