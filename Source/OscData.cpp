/*
  ==============================================================================

    OscData.cpp
    Created: 2 May 2021 2:17:40pm
    Author:  Zombori Márk

  ==============================================================================
*/

#include "OscData.h"

void OscData:: prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    fmOsc.prepare(spec);
    lfoOsc.prepare(spec);
    prepare(spec);
    gain.prepare(spec);
    sampleRateUse=spec.sampleRate;
    
}

void OscData::setWaveType(const int choice)
{
    
    switch (choice) {
        case 0:
            // sine wave
            initialise([](float x) {return std::sin(x); });
            break;
            
        case 1:
            // saw wave
            initialise([](float x) {return x/ juce::MathConstants<float>::pi; });
            break;
            
        case 2:
            // square wave
            initialise([](float x) {return x<0.0f ? -1.0f :1.0f; });
            break;
            
        default:
            jassertfalse;
            break;
    }
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    if(midiNoteNumber!=lastMidiNote)
    {
        if(isGlide){
            glideCounter=0;
            if(lastMidiNote!=0){
                glideHappening=true;
                fromGlideMidiNote=lastMidiNote;
            }
            
            lastMidiNote=midiNoteNumber;
        }
        else{
            setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber+lastPitch)+fmMod+detuner);
            lastMidiNote=midiNoteNumber;
        }
    }
}

void OscData::gliding()
{
    //if(isGlide){
        if (glideCounter==glider)
        {
            glideHappening=false;
            glideCounter=0;
        }
        else
        {
            helper=((juce::MidiMessage::getMidiNoteInHertz(lastMidiNote+lastPitch)-juce::MidiMessage::getMidiNoteInHertz(fromGlideMidiNote+lastPitch))/glider)*glideCounter+juce::MidiMessage::getMidiNoteInHertz(fromGlideMidiNote+lastPitch);
            glideCounter++;
        }

}

void OscData::getNewAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    /*for (int ch=0; ch<block.getNumChannels(); ch++)
    {
        for(int s=0; s<block.getNumSamples(); s++)
        {
            fmMod=fmOsc.processSample(block.getSample(ch, s))*fmDepth;
            //lfoMod=lfoOsc.processSample(block.getSample(ch, s))*lfoDepth;
        }
    }
    
    process(juce::dsp::ProcessContextReplacing<float> (block));
    gain.process (juce::dsp::ProcessContextReplacing<float> (block));
    */
}

void OscData::setFmParams(const float depth, const float freq)
{
    fmOsc.setFrequency(freq);
    fmDepth=depth;
    //auto currentFreq=juce::MidiMessage::getMidiNoteInHertz(lastMidiNote)+fmMod;
    //setFrequency(currentFreq>=0 ? currentFreq: currentFreq* -1.0f);
    //setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote+lastPitch)+fmMod+detuner);
    if(isGlide){
        setFrequency(helper+fmMod+detuner);
    }
    else{
        setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote+lastPitch)+fmMod+detuner);
    }
}

void OscData::setLfoParams(const float depth, const float freq)
{
    lfoOsc.setFrequency(freq*48);
    lfoDepth=depth;
}

void OscData::setGain(const float levelInDecibels)
{
    //juce::dsp::decibelsToGain<float>(levelInDecibels);
    gain.setGainDecibels(levelInDecibels+lfoMod);
}

void OscData::setPitch(const int pitch)
{
    lastPitch=pitch;
    //setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote+lastPitch)+fmMod+detuner);
    if(isGlide){
        setFrequency(helper+fmMod+detuner);
    }
    else{
        setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote+lastPitch)+fmMod+detuner);
    }
}

void OscData::setDetuner(const float detune)
{
    detuner=detune;
    //setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote+lastPitch)+fmMod+detuner);
    if(isGlide){
        setFrequency(helper+fmMod+detuner);
    }
    else{
        setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote+lastPitch)+fmMod+detuner);
    }
}

void OscData::setGlide(const int glide)
{
    glider=glide;
    isGlide=(glide!=0);
}

float OscData::processNextSample (float input)
{
    //input=0;
    fmMod = fmOsc.processSample (input) * fmDepth;
    if (counter==48)
    {
       
        
        lfoMod = lfoOsc.processSample (input) * lfoDepth;
        counter=0;
    }
    counter++;
   
    if (glideHappening)
    {
        gliding();
        setFrequency(helper+fmMod+detuner);
    }
    
    lastProcessSample=gain.processSample (processSample (input));

    return gain.processSample (processSample (input));
}
