/*
  ==============================================================================

    OscComponent.cpp
    Created: 2 May 2021 2:18:18pm
    Author:  Zombori Márk

  ==============================================================================
*/

#include "OscComponent.h"
#include <JuceHeader.h>

OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String name, juce::String waveSelectorID, juce::String fmFreqId, juce::String fmDepthId, juce::String gainId, juce::String pitchId)
{
    componentName=name;
    
    juce::StringArray choices {"Sine", "Saw", "Square"};
    oscWaveSelector.addItemList(choices, 1);
    addAndMakeVisible(oscWaveSelector);
    oscWaveSelectorAttachment=std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorID, oscWaveSelector);
    
    fmFreqSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fmFreqSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible (fmFreqSlider);
    fmFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmFreqId, fmFreqSlider);
    fmFreqLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    fmFreqLabel.setFont(15.0f);
    fmFreqLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(fmFreqLabel);
    
    fmDepthSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fmDepthSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible (fmDepthSlider);
    fmDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmDepthId, fmDepthSlider);
    fmDepthLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    fmDepthLabel.setFont(15.0f);
    fmDepthLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(fmDepthLabel);
    
    gainSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible (gainSlider);
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, gainId, gainSlider);
    gainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    gainLabel.setFont(15.0f);
    gainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(gainLabel);
    
    pitchSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    pitchSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible (pitchSlider);
    pitchAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, pitchId, pitchSlider);
    pitchLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    pitchLabel.setFont(15.0f);
    pitchLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(pitchLabel);
    //setSliderWithLabel(fmFreqSlider, fmFreqLabel, apvts, fmFreqId, fmFreqAttachment);
    //setSliderWithLabel(fmDepthSlider, fmDepthLabel, apvts, fmDepthId, fmDepthAttachment);
    
    
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    auto bounds=getLocalBounds().reduced(40);
    auto labelSpace=bounds.removeFromTop(25.0f);
    
    g.fillAll(juce::Colours::black);
    g.drawText(componentName, labelSpace.withX(20), juce::Justification::right);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void OscComponent::resized()
{
    const auto sliderWidth=100;
    const auto sliderHeight=80;
    const auto labelYOff=20;
    const auto labelHeight=20;
    const auto sliderPosY=50;
    
    oscWaveSelector.setBounds(0, 0, 90, 20);
    fmFreqSlider.setBounds(0, sliderPosY, sliderWidth, sliderHeight);
    fmFreqLabel.setBounds(fmFreqSlider.getX(), fmFreqSlider.getY()-labelYOff, fmFreqSlider.getWidth(), labelHeight);
    fmDepthSlider.setBounds(fmFreqSlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
    fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY()-labelYOff, fmDepthSlider.getWidth(), labelHeight);
    gainSlider.setBounds(fmDepthSlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
    gainLabel.setBounds(gainSlider.getX(), gainSlider.getY()-labelYOff, gainSlider.getWidth(), labelHeight);
    pitchSlider.setBounds(gainSlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
    pitchLabel.setBounds(pitchSlider.getX(), pitchSlider.getY()-labelYOff, pitchSlider.getWidth(), labelHeight);
}

using Attachment= juce::AudioProcessorValueTreeState::SliderAttachment;
void OscComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
    
    attachment=std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (apvts, paramId, slider);
    
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}
