/*
  ==============================================================================

    OscComponent.cpp
    Created: 2 May 2021 2:18:18pm
    Author:  Zombori Márk

  ==============================================================================
*/

#include "OscComponent.h"
#include <JuceHeader.h>

OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String name, juce::String waveSelectorID, juce::String fmFreqId, juce::String fmDepthId, juce::String gainId, juce::String pitchId, juce::String lfoFreqId,juce::String lfoFreqRateId, juce::String lfoDepthId, juce::String detunerId, juce::String HorR)
{
    componentName=name;
    
    auto bounds=getLocalBounds();
    float font=bounds.getHeight()/5;
    int vmiWeight=50;
    int vmiHeight=20;
    font=14.0f;
    
    //setTransform(const AffineTransform &transform);
    
    juce::StringArray choices {"Sine", "Saw", "Square"};
    oscWaveSelector.addItemList(choices, 1);
    oscWaveSelector.setLookAndFeel(&comboBoxLookAndFeel);
    addAndMakeVisible(oscWaveSelector);
    oscWaveSelectorAttachment=std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorID, oscWaveSelector);
    
    
    fmFreqSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fmFreqSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, vmiWeight, vmiHeight);
    fmFreqSlider.setLookAndFeel(&sliderLookAndFeel);
    addAndMakeVisible (fmFreqSlider);
    fmFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmFreqId, fmFreqSlider);
    fmFreqLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    fmFreqLabel.setFont(font);
    fmFreqLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(fmFreqLabel);
    
    fmDepthSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    fmDepthSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, vmiWeight, vmiHeight);
    fmDepthSlider.setLookAndFeel(&sliderLookAndFeel);
    addAndMakeVisible (fmDepthSlider);
    fmDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmDepthId, fmDepthSlider);
    fmDepthLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    fmDepthLabel.setFont(font);
    fmDepthLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(fmDepthLabel);
    
    lfoFreqSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lfoFreqSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, vmiWeight, vmiHeight);
    lfoFreqSlider.setLookAndFeel(&sliderLookAndFeel);
    addAndMakeVisible (lfoFreqSlider);
    lfoFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, lfoFreqId, lfoFreqSlider);
    lfoFreqLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    lfoFreqLabel.setFont(font);
    lfoFreqLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(lfoFreqLabel);
    
    lfoFreqRSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lfoFreqRSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, vmiWeight, vmiHeight);
    lfoFreqRSlider.setLookAndFeel(&sliderLookAndFeel);
    addAndMakeVisible (lfoFreqRSlider);
    lfoFreqRAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, lfoFreqRateId, lfoFreqRSlider);
    lfoFreqRateLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    lfoFreqRateLabel.setFont(font);
    lfoFreqRateLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(lfoFreqRateLabel);
    
    lfoDepthSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lfoDepthSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, vmiWeight, vmiHeight);
    lfoDepthSlider.setLookAndFeel(&sliderLookAndFeel);
    addAndMakeVisible (lfoDepthSlider);
    lfoDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, lfoDepthId, lfoDepthSlider);
    lfoDepthLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    lfoDepthLabel.setFont(font);
    lfoDepthLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(lfoDepthLabel);
    
    gainSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, vmiWeight, vmiHeight);
    gainSlider.setLookAndFeel(&sliderLookAndFeel);
    addAndMakeVisible (gainSlider);
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, gainId, gainSlider);
    gainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    gainLabel.setFont(font);
    gainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(gainLabel);
    
    pitchSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    pitchSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, vmiWeight, vmiHeight);
    pitchSlider.setLookAndFeel(&otherSliderLookAndFeel);
    addAndMakeVisible (pitchSlider);
    pitchAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, pitchId, pitchSlider);
    pitchLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    pitchLabel.setFont(font);
    pitchLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(pitchLabel);
    
    detunerSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    detunerSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, vmiWeight, vmiHeight);
    detunerSlider.setLookAndFeel(&otherSliderLookAndFeel);
    addAndMakeVisible (detunerSlider);
    detunerAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, detunerId, detunerSlider);
    detunerLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    detunerLabel.setFont(font);
    detunerLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(detunerLabel);
    
    //setSliderWithLabel(fmFreqSlider, fmFreqLabel, apvts, fmFreqId, fmFreqAttachment);
    //setSliderWithLabel(fmDepthSlider, fmDepthLabel, apvts, fmDepthId, fmDepthAttachment);
    
    horRValue =apvts.getParameterAsValue("HORR");
    horRisHertz=(horRValue.toString()=="0.0");
    
}

OscComponent::~OscComponent()
{
    oscWaveSelector.setLookAndFeel(nullptr);
    fmFreqSlider.setLookAndFeel(nullptr);
    fmDepthSlider.setLookAndFeel(nullptr);
    lfoFreqSlider.setLookAndFeel(nullptr);
    lfoFreqRSlider.setLookAndFeel(nullptr);
    lfoDepthSlider.setLookAndFeel(nullptr);
    gainSlider.setLookAndFeel(nullptr);
    pitchSlider.setLookAndFeel(nullptr);
    detunerSlider.setLookAndFeel(nullptr);
}

void OscComponent::paint (juce::Graphics& g)
{
    auto bounds=getLocalBounds();
    auto labelSpace=bounds.removeFromTop(25.0f);
    float font=bounds.getHeight()/5;
    
    g.fillAll(juce::Colours::steelblue);
    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
    
    g.setColour (juce::Colours::white);
    g.setFont (font);
    g.setFont (g.getCurrentFont().boldened());
    g.drawText(componentName, labelSpace.withX(0), juce::Justification::left);
}

void OscComponent::resized()
{
    auto sliderWidth=70;
    auto sliderHeight=70;
    auto labelYOff=20;
    auto labelHeight=20;
    auto sliderPosY=50;
    
    juce::Rectangle<int> bounds = getLocalBounds();
    sliderWidth=bounds.getWidth()/7;
    sliderHeight=bounds.getHeight()/2+10;
    labelHeight=sliderHeight/3;
    labelYOff=sliderHeight/4;
    sliderPosY=labelHeight*2;
    
    oscWaveSelector.setBounds(4.5*sliderWidth, 0, sliderWidth*2.5, labelHeight);
    fmFreqSlider.setBounds(0, sliderPosY, sliderWidth, sliderHeight);
    fmFreqLabel.setBounds(fmFreqSlider.getX(), fmFreqSlider.getY()-labelYOff, fmFreqSlider.getWidth(), labelHeight);
    fmDepthSlider.setBounds(fmFreqSlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
    fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY()-labelYOff, fmDepthSlider.getWidth(), labelHeight);
    
    
    if (horRisHertz){
        lfoFreqRSlider.setBounds(fmDepthSlider.getRight(), sliderPosY, 0, 0);
        lfoFreqRateLabel.setBounds(lfoFreqRSlider.getX(), lfoFreqRSlider.getY()-labelYOff, 0, 0);
        
        lfoFreqSlider.setBounds(fmDepthSlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
        lfoFreqLabel.setBounds(lfoFreqSlider.getX(), lfoFreqSlider.getY()-labelYOff, fmFreqSlider.getWidth(), labelHeight);

        lfoDepthSlider.setBounds(lfoFreqSlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
        lfoDepthLabel.setBounds(lfoDepthSlider.getX(), lfoDepthSlider.getY()-labelYOff, fmDepthSlider.getWidth(), labelHeight);
    }
    else{
        lfoFreqSlider.setBounds(fmDepthSlider.getRight(), sliderPosY, 0, 0);
        lfoFreqLabel.setBounds(lfoFreqSlider.getX(), lfoFreqSlider.getY()-labelYOff, 0, 0);
        
        lfoFreqRSlider.setBounds(fmDepthSlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
        lfoFreqRateLabel.setBounds(lfoFreqRSlider.getX(), lfoFreqRSlider.getY()-labelYOff, fmFreqSlider.getWidth(), labelHeight);
        
        lfoDepthSlider.setBounds(lfoFreqRSlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
        lfoDepthLabel.setBounds(lfoDepthSlider.getX(), lfoDepthSlider.getY()-labelYOff, fmDepthSlider.getWidth(), labelHeight);
    }
    gainSlider.setBounds(lfoDepthSlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
    gainLabel.setBounds(gainSlider.getX(), gainSlider.getY()-labelYOff, gainSlider.getWidth(), labelHeight);
    pitchSlider.setBounds(gainSlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
    pitchLabel.setBounds(pitchSlider.getX(), pitchSlider.getY()-labelYOff, pitchSlider.getWidth(), labelHeight);
    detunerSlider.setBounds(pitchSlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
    detunerLabel.setBounds(detunerSlider.getX(), detunerSlider.getY()-labelYOff, detunerSlider.getWidth(), labelHeight);
    
    
}

