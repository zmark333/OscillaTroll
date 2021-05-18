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
        osc1 (audioProcessor.apvts, "OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH", "OSC1GAIN", "OSC1PITCH"),
        osc2 (audioProcessor.apvts, "OSC2WAVETYPE", "OSC2FMFREQ", "OSC2FMDEPTH", "OSC2GAIN", "OSC2PITCH"),
        osc3 (audioProcessor.apvts, "OSC3WAVETYPE", "OSC3FMFREQ", "OSC3FMDEPTH", "OSC3GAIN", "OSC3PITCH"),
        adsr ("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
{
    setSize (900, 700);
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(osc3);
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
    const auto paddingY=35;
    const auto paddingYplus=200;
    const auto width=400;
    const auto height=150;
    
    osc1.setBounds(paddingX, paddingY, width, height);
    adsr.setBounds(osc1.getRight(),paddingY,width, 300);
    osc2.setBounds( paddingX, 185, width, height);
    osc3.setBounds( paddingX, 335, width, height);
}
