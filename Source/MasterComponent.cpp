/*
  ==============================================================================

    MasterComponent.cpp
    Created: 28 May 2021 1:45:37pm
    Author:  Zombori Márk

  ==============================================================================
*/

#include "MasterComponent.h"
#include "JuceHeader.h"


MasterComponent::MasterComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String masterId, juce::String MorGSelectorID, juce::String HorRSelectorID)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    componentName=name;
    
    masterAttachment = std::make_unique<SliderAttachment>(apvts, "MASTERGAIN",masterSlider);
    
    masterSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    masterSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    masterSlider.setLookAndFeel(&sliderLookAndFeel);
    addAndMakeVisible(masterSlider);
    
    glideAttachment = std::make_unique<SliderAttachment>(apvts, "GLIDE",glideSlider);
    
    glideSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    glideSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    glideSlider.setLookAndFeel(&sliderLookAndFeel);
    addAndMakeVisible(glideSlider);
    
    float font=14.0f;
    
    masterLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    masterLabel.setFont(font);
    masterLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(masterLabel);
    
    glideLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    glideLabel.setFont(font);
    glideLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(glideLabel);
    
    juce::StringArray choices {"Multi-touch", "Glider"};
    MorGBox.addItemList(choices, 1);
    MorGBox.setLookAndFeel(&comboBoxLookAndFeel);
    addAndMakeVisible(MorGBox);
    MorGAttachment=std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, MorGSelectorID, MorGBox);
    
    
    
}

MasterComponent::~MasterComponent()
{
    masterSlider.setLookAndFeel(nullptr);
    glideSlider.setLookAndFeel(nullptr);
    MorGBox.setLookAndFeel(nullptr);
}

void MasterComponent::paint (juce::Graphics& g)
{
    auto bounds=getLocalBounds();
    auto labelSpace=bounds.removeFromTop(25.0f);
    float font=bounds.getHeight()/10;
    

    
    
    g.setColour (juce::Colours::white);
    g.setFont (font);
    g.setFont (g.getCurrentFont().boldened());
    g.drawText(componentName, labelSpace.withX(0), juce::Justification::left);
}

void MasterComponent::resized()
{
    const auto bounds=getLocalBounds().reduced(10);
    const auto padding=10;
    const auto sliderWidth=bounds.getWidth()/2-padding;
    const auto sliderHeight=bounds.getHeight()/2.5;
    const auto sliderStartX=10;
    const auto sliderStartY=bounds.getHeight()/5;
    auto labelHeight=sliderHeight/6;
    auto labelYOff=sliderHeight/8;
    
    
    glideSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    glideLabel.setBounds(glideSlider.getX(), glideSlider.getY()-labelYOff, glideSlider.getWidth(), labelHeight);
    
    masterSlider.setBounds(glideSlider.getRight(), sliderStartY, sliderWidth, sliderHeight);
    masterLabel.setBounds(masterSlider.getX(), masterSlider.getY()-labelYOff, masterSlider.getWidth(), labelHeight);
    
    MorGBox.setBounds(sliderStartX, glideSlider.getY()+8*padding, 2*sliderWidth, sliderHeight/3);
    
}
