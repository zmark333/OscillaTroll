/*
  ==============================================================================

    SynthSound.h
    Created: 2 May 2021 2:16:46pm
    Author:  Zombori Márk

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNotNumber) override {return true;}
    bool appliesToChannel (int midiChannel) override {return true;}
    
};
