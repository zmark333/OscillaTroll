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
        osc1 (audioProcessor.apvts,"Oscillator 1", "OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH", "OSC1GAIN", "OSC1PITCH"),
        osc2 (audioProcessor.apvts, "Oscillator 2", "OSC2WAVETYPE", "OSC2FMFREQ", "OSC2FMDEPTH", "OSC2GAIN", "OSC2PITCH"),
        osc3 (audioProcessor.apvts, "Oscillator 3", "OSC3WAVETYPE", "OSC3FMFREQ", "OSC3FMDEPTH", "OSC3GAIN", "OSC3PITCH"),
        osc4 (audioProcessor.apvts, "Oscillator 4", "OSC4WAVETYPE", "OSC4FMFREQ", "OSC4FMDEPTH", "OSC4GAIN", "OSC4PITCH"),
        osc5 (audioProcessor.apvts, "Oscillator 5", "OSC5WAVETYPE", "OSC5FMFREQ", "OSC5FMDEPTH", "OSC5GAIN", "OSC5PITCH"),
        osc6 (audioProcessor.apvts, "Oscillator 6", "OSC6WAVETYPE", "OSC6FMFREQ", "OSC6FMDEPTH", "OSC6GAIN", "OSC6PITCH"),
        osc7 (audioProcessor.apvts, "Oscillator 7", "OSC7WAVETYPE", "OSC7FMFREQ", "OSC7FMDEPTH", "OSC7GAIN", "OSC7PITCH"),
        osc8 (audioProcessor.apvts, "Oscillator 8", "OSC8WAVETYPE", "OSC8FMFREQ", "OSC8FMDEPTH", "OSC8GAIN", "OSC8PITCH"),
        osc9 (audioProcessor.apvts, "Oscillator 9", "OSC9WAVETYPE", "OSC9FMFREQ", "OSC9FMDEPTH", "OSC9GAIN", "OSC9PITCH"),
        osc10 (audioProcessor.apvts, "Oscillator 10", "OSC10WAVETYPE", "OSC10FMFREQ", "OSC10FMDEPTH", "OSC10GAIN", "OSC10PITCH"),
        adsr ("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
{
    setSize (1200, 700);
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
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void OscillaTroll02AudioProcessorEditor::resized()
{
    const auto paddingX=5;
    const auto paddingY=0;
    const auto paddingYplus=200;
    const auto width=400;
    const auto height=140;
    
    osc1.setBounds(paddingX, paddingY, width, height);
    osc2.setBounds( paddingX, 140, width, height);
    osc3.setBounds( paddingX, 280, width, height);
    osc4.setBounds( paddingX, 420, width, height);
    osc5.setBounds( paddingX, 560, width, height);
    osc6.setBounds(osc1.getRight(), paddingY, width, height);
    osc7.setBounds( osc1.getRight(), 140, width, height);
    osc8.setBounds( osc1.getRight(), 280, width, height);
    osc9.setBounds( osc1.getRight(), 420, width, height);
    osc10.setBounds( osc1.getRight(), 560, width, height);
    adsr.setBounds(osc6.getRight(),paddingY,width, 300);
    
}
