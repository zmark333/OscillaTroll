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
    
    float font=14.0f;
    
    attackLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    attackLabel.setFont(font);
    attackLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(attackLabel);
    
    decayLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    decayLabel.setFont(font);
    decayLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(decayLabel);
    
    sustainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    sustainLabel.setFont(font);
    sustainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(sustainLabel);
    
    releaseLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    releaseLabel.setFont(font);
    releaseLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(releaseLabel);
    
    
}

AdsrComponent::~AdsrComponent()
{
    attackSlider.setLookAndFeel(nullptr);
    decaySlider.setLookAndFeel(nullptr);
    sustainSlider.setLookAndFeel(nullptr);
    releaseSlider.setLookAndFeel(nullptr);
}

void AdsrComponent::paint (juce::Graphics& g)
{
    auto bounds=getLocalBounds();
    auto labelSpace=bounds.removeFromTop(25.0f);
    float font=bounds.getHeight()/10;
    
    g.fillAll(juce::Colours::steelblue);
    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
    
    g.setColour (juce::Colours::white);
    g.setFont (font);
    g.setFont (g.getCurrentFont().boldened());
    g.drawText(componentName, labelSpace.withX(0), juce::Justification::left);
}

void AdsrComponent::resized()
{
    const auto bounds=getLocalBounds().reduced(10);
    const auto padding=10;
    const auto sliderWidth=bounds.getWidth()/4-padding;
    const auto sliderHeight=bounds.getHeight()/1.5;
    const auto sliderStartX=10;
    const auto sliderStartY=bounds.getHeight()/4;
    auto labelHeight=sliderHeight/6;
    auto labelYOff=sliderHeight/8;
    
    
    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    attackLabel.setBounds(attackSlider.getX(), attackSlider.getY()-labelYOff, attackSlider.getWidth(), labelHeight);
    decaySlider.setBounds(attackSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    decayLabel.setBounds(decaySlider.getX(), decaySlider.getY()-labelYOff, decaySlider.getWidth(), labelHeight);
    sustainSlider.setBounds(decaySlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    sustainLabel.setBounds(sustainSlider.getX(), sustainSlider.getY()-labelYOff, sustainSlider.getWidth(), labelHeight);
    releaseSlider.setBounds(sustainSlider.getRight()+padding, sliderStartY, sliderWidth, sliderHeight);
    releaseLabel.setBounds(releaseSlider.getX(), releaseSlider.getY()-labelYOff, releaseSlider.getWidth(), labelHeight);
    
    
}

void AdsrComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    slider.setLookAndFeel(&sliderLookAndFeel);
    addAndMakeVisible(slider);
}

