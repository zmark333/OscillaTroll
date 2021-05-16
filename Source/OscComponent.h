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
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorID, juce::String fmFreqId, juce::String fmDepthId, juce::String gainId);
    ~OscComponent() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    juce::ComboBox oscWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;
    
    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
    juce::Slider gainSlider;
    
    using Attachment=juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<Attachment> fmFreqAttachment;
    std::unique_ptr<Attachment> fmDepthAttachment;
    std::unique_ptr<Attachment> gainAttachment;
    
    juce::Label fmFreqLabel{"FM Freq", "FM Freq"};
    juce::Label fmDepthLabel{"FM Depth", "FM Depth"};

    
    
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
