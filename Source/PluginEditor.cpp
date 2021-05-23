/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OscillaTroll02AudioProcessorEditor::OscillaTroll02AudioProcessorEditor (OscillaTroll02AudioProcessor& p)
        : AudioProcessorEditor (&p), audioProcessor (p),
        osc1 (audioProcessor.apvts, "Oscillator 1", "OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH", "OSC1GAIN", "OSC1PITCH", "OSC1LFOFREQ", "OSC1LFODEPTH", "OSC1DETUNE"),
        osc2 (audioProcessor.apvts, "Oscillator 2", "OSC2WAVETYPE", "OSC2FMFREQ", "OSC2FMDEPTH", "OSC2GAIN", "OSC2PITCH", "OSC2LFOFREQ", "OSC2LFODEPTH", "OSC2DETUNE"),
        osc3 (audioProcessor.apvts, "Oscillator 3", "OSC3WAVETYPE", "OSC3FMFREQ", "OSC3FMDEPTH", "OSC3GAIN", "OSC3PITCH", "OSC3LFOFREQ", "OSC3LFODEPTH", "OSC3DETUNE"),
        osc4 (audioProcessor.apvts, "Oscillator 4", "OSC4WAVETYPE", "OSC4FMFREQ", "OSC4FMDEPTH", "OSC4GAIN", "OSC4PITCH", "OSC4LFOFREQ", "OSC4LFODEPTH", "OSC4DETUNE"),
        osc5 (audioProcessor.apvts, "Oscillator 5", "OSC5WAVETYPE", "OSC5FMFREQ", "OSC5FMDEPTH", "OSC5GAIN", "OSC5PITCH", "OSC5LFOFREQ", "OSC5LFODEPTH", "OSC5DETUNE"),
        osc6 (audioProcessor.apvts, "Oscillator 6", "OSC6WAVETYPE", "OSC6FMFREQ", "OSC6FMDEPTH", "OSC6GAIN", "OSC6PITCH", "OSC6LFOFREQ", "OSC6LFODEPTH", "OSC6DETUNE"),
        osc7 (audioProcessor.apvts, "Oscillator 7", "OSC7WAVETYPE", "OSC7FMFREQ", "OSC7FMDEPTH", "OSC7GAIN", "OSC7PITCH", "OSC7LFOFREQ", "OSC7LFODEPTH", "OSC7DETUNE"),
        osc8 (audioProcessor.apvts, "Oscillator 8", "OSC8WAVETYPE", "OSC8FMFREQ", "OSC8FMDEPTH", "OSC8GAIN", "OSC8PITCH", "OSC8LFOFREQ", "OSC8LFODEPTH", "OSC8DETUNE"),
        osc9 (audioProcessor.apvts, "Oscillator 9", "OSC9WAVETYPE", "OSC9FMFREQ", "OSC9FMDEPTH", "OSC9GAIN", "OSC9PITCH", "OSC9LFOFREQ", "OSC9LFODEPTH", "OSC9DETUNE"),
        osc10 (audioProcessor.apvts, "Oscillator 10", "OSC10WAVETYPE", "OSC10FMFREQ", "OSC10FMDEPTH", "OSC10GAIN", "OSC10PITCH", "OSC10LFOFREQ", "OSC10LFODEPTH", "OSC10DETUNE"),
        adsr ("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
{
    setResizable(true, true);
    setSize (900, 500);
    setResizeLimits(600, 450, 1400, 1200);

    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(osc3);
    addAndMakeVisible(osc4);
    addAndMakeVisible(osc5);
    addAndMakeVisible(osc6);
    addAndMakeVisible(osc7);
    addAndMakeVisible(osc8);
    addAndMakeVisible(osc9);
    addAndMakeVisible(osc10);
    addAndMakeVisible(adsr);
}

OscillaTroll02AudioProcessorEditor::~OscillaTroll02AudioProcessorEditor()
{
}

//==============================================================================
void OscillaTroll02AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::steelblue);

}

void OscillaTroll02AudioProcessorEditor::resized()
{
    juce::Rectangle<int> bounds = getLocalBounds();
    const auto paddingX=5;
    const auto paddingY=5;
    auto width=490;
    auto height=140;
    
    width=(bounds.getWidth()-4*paddingX)/2.5;
    height=(bounds.getHeight()-5*paddingY)/5;
    
    
    osc1.setBounds(paddingX, 0, width, height);
    osc2.setBounds( paddingX, height+paddingY, width, height);
    osc3.setBounds( paddingX, 2*(height+paddingY), width, height);
    osc4.setBounds( paddingX, 3*(height+paddingY), width, height);
    osc5.setBounds( paddingX, 4*(height+paddingY), width, height);
    osc6.setBounds(osc1.getRight()+paddingX, 0, width, height);
    osc7.setBounds( osc1.getRight()+paddingX, (height+paddingY), width, height);
    osc8.setBounds( osc1.getRight()+paddingX, 2*(height+paddingY), width, height);
    osc9.setBounds( osc1.getRight()+paddingX, 3*(height+paddingY), width, height);
    osc10.setBounds( osc1.getRight()+paddingX, 4*(height+paddingY), width, height);
    adsr.setBounds(osc6.getRight()+paddingX,paddingY,width/2, 2*height-paddingY);
    
    

}
