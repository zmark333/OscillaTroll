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
        osc1 (audioProcessor.apvts, "OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH", "OSC1GAIN"),
        osc2 (audioProcessor.apvts, "OSC2WAVETYPE", "OSC2FMFREQ", "OSC2FMDEPTH", "OSC2GAIN"),
        adsr ("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
{
    setSize (800, 600);
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
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
    const auto paddingY2=235;
    const auto width=300;
    const auto height=200;
    
    osc1.setBounds(paddingX, paddingY, width, height);
    adsr.setBounds(osc1.getRight(),paddingY,width, height);
    osc2.setBounds( paddingX, paddingY2, width, height);
}
