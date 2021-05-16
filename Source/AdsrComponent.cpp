/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 2 May 2021 2:18:33pm
    Author:  Zombori Márk

  ==============================================================================
*/

#include "AdsrComponent.h"
#include <JuceHeader.h>

AdsrComponent::AdsrComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    componentName=name;
    
    attackAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK",attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY",decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN",sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE",releaseSlider);
    
    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);
    
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    auto bounds=getLocalBounds().reduced(5);
    auto labelSpace=bounds.removeFromTop(25.0f);
    
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText(componentName, labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void AdsrComponent::resized()
{
    const auto bounds=getLocalBounds().reduced(10);
    const auto padding=10;
    const auto sliderWidth=bounds.getWidth()/4-padding;
    const auto sliderHeight=bounds.getHeight();
    const auto sliderStartX=0;
    const auto sliderStartY=0;
    
    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    
    
}

void AdsrComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}

