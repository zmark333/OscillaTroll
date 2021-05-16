/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OscillaTroll02AudioProcessor::OscillaTroll02AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", createParams())
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

OscillaTroll02AudioProcessor::~OscillaTroll02AudioProcessor()
{
}

//==============================================================================
const juce::String OscillaTroll02AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool OscillaTroll02AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool OscillaTroll02AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool OscillaTroll02AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double OscillaTroll02AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OscillaTroll02AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int OscillaTroll02AudioProcessor::getCurrentProgram()
{
    return 0;
}

void OscillaTroll02AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String OscillaTroll02AudioProcessor::getProgramName (int index)
{
    return {};
}

void OscillaTroll02AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void OscillaTroll02AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for(int i=0; i<synth.getNumVoices(); i++)
    {
        if(auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void OscillaTroll02AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool OscillaTroll02AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void OscillaTroll02AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int i=0; i<synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            auto& attack=*apvts.getRawParameterValue("ATTACK");
            auto& decay=*apvts.getRawParameterValue("DECAY");
            auto& sustain=*apvts.getRawParameterValue("SUSTAIN");
            auto& release=*apvts.getRawParameterValue("RELEASE");
            
            auto& oscWaveChoice1=*apvts.getRawParameterValue("OSC1WAVETYPE");
            auto& fmFrequ1=*apvts.getRawParameterValue("OSC1FMFREQ");
            auto& fmDepth1=*apvts.getRawParameterValue("OSC1FMDEPTH");
            auto& levelInDecibels1=*apvts.getRawParameterValue("OSC1GAIN");
            
            auto& oscWaveChoice2=*apvts.getRawParameterValue("OSC2WAVETYPE");
            auto& fmFrequ2=*apvts.getRawParameterValue("OSC2FMFREQ");
            auto& fmDepth2=*apvts.getRawParameterValue("OSC2FMDEPTH");
            auto& levelInDecibels2=*apvts.getRawParameterValue("OSC2GAIN");
            
            voice->getOscillator1().setWaveType(oscWaveChoice1);
            voice->getOscillator1().setFmParams(fmDepth1, fmFrequ1);
            voice->getOscillator1().setGain(levelInDecibels1);
            voice->getOscillator2().setWaveType(oscWaveChoice2);
            voice->getOscillator2().setFmParams(fmDepth2, fmFrequ2);
            voice->getOscillator2().setGain(levelInDecibels2);
            voice->updateAdsr(attack.load(), decay.load(), sustain.load(), release.load());
        }
    }
    
   // for(const juce::MidiMessageMetadata metadata: midiMessages)
     //   if(metadata.numBytes ==3)
        //    juce::Logger::writeToLog("TimeStamp: "+juce::String (metadata.getMessage().getTimeStamp()));
    
    
    synth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool OscillaTroll02AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* OscillaTroll02AudioProcessor::createEditor()
{
    return new OscillaTroll02AudioProcessorEditor (*this);
}

//==============================================================================
void OscillaTroll02AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void OscillaTroll02AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OscillaTroll02AudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout OscillaTroll02AudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    //Osc select
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1WAVETYPE", "Osc 1 Wave Type", juce::StringArray {"Sine", "Saw", "Square"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC2WAVETYPE", "Osc 2 Wave Type", juce::StringArray {"Sine", "Saw", "Square"}, 0));
    
    //Gain
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC1GAIN", "Oscillator 1 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, 0.1f, "dB"));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC2GAIN", "Oscillator 2 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, 0.1f, "dB"));

    
    //FM
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMFREQ","Osc 1 FM Frequency",juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMDEPTH","Osc 1 FM Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2FMFREQ","Osc 2 FM Frequency",juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2FMDEPTH","Osc 2 FM Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f, 0.3f},0.0f));
    
    
    //ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK","Attack",juce::NormalisableRange<float> {0.1f, 1.0f},0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY","Decay",juce::NormalisableRange<float> {0.1f, 1.0f},0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN","Sustain",juce::NormalisableRange<float> {0.1f, 1.0f},1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE","Release",juce::NormalisableRange<float> {0.1f, 3.0f},0.4f));
    

    return {params.begin(), params.end()};
    
}

