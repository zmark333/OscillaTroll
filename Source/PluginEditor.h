/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "AdsrComponent.h"
#include "OscComponent.h"


//==============================================================================
/**
*/
class OscillaTroll02AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    OscillaTroll02AudioProcessorEditor (OscillaTroll02AudioProcessor&);
    ~OscillaTroll02AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    OscillaTroll02AudioProcessor& audioProcessor;
    OscComponent osc1;
    OscComponent osc2;
    AdsrComponent adsr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillaTroll02AudioProcessorEditor)
};
