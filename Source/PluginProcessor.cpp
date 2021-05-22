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
            auto& lfoFrequ1=*apvts.getRawParameterValue("OSC1LFOFREQ");
            auto& lfoDepth1=*apvts.getRawParameterValue("OSC1LFODEPTH");
            auto& levelInDecibels1=*apvts.getRawParameterValue("OSC1GAIN");
            auto& oscPitch1=*apvts.getRawParameterValue("OSC1PITCH");
            auto& detune1=*apvts.getRawParameterValue("OSC1DETUNE");
            
            auto& oscWaveChoice2=*apvts.getRawParameterValue("OSC2WAVETYPE");
            auto& fmFrequ2=*apvts.getRawParameterValue("OSC2FMFREQ");
            auto& fmDepth2=*apvts.getRawParameterValue("OSC2FMDEPTH");
            auto& lfoFrequ2=*apvts.getRawParameterValue("OSC2LFOFREQ");
            auto& lfoDepth2=*apvts.getRawParameterValue("OSC2LFODEPTH");
            auto& levelInDecibels2=*apvts.getRawParameterValue("OSC2GAIN");
            auto& oscPitch2=*apvts.getRawParameterValue("OSC2PITCH");
            auto& detune2=*apvts.getRawParameterValue("OSC2DETUNE");
            
            auto& oscWaveChoice3=*apvts.getRawParameterValue("OSC3WAVETYPE");
            auto& fmFrequ3=*apvts.getRawParameterValue("OSC3FMFREQ");
            auto& fmDepth3=*apvts.getRawParameterValue("OSC3FMDEPTH");
            auto& lfoFrequ3=*apvts.getRawParameterValue("OSC3LFOFREQ");
            auto& lfoDepth3=*apvts.getRawParameterValue("OSC3LFODEPTH");
            auto& levelInDecibels3=*apvts.getRawParameterValue("OSC3GAIN");
            auto& oscPitch3=*apvts.getRawParameterValue("OSC3PITCH");
            auto& detune3=*apvts.getRawParameterValue("OSC3DETUNE");
            
            auto& oscWaveChoice4=*apvts.getRawParameterValue("OSC4WAVETYPE");
            auto& fmFrequ4=*apvts.getRawParameterValue("OSC4FMFREQ");
            auto& fmDepth4=*apvts.getRawParameterValue("OSC4FMDEPTH");
            auto& lfoFrequ4=*apvts.getRawParameterValue("OSC4LFOFREQ");
            auto& lfoDepth4=*apvts.getRawParameterValue("OSC4LFODEPTH");
            auto& levelInDecibels4=*apvts.getRawParameterValue("OSC4GAIN");
            auto& oscPitch4=*apvts.getRawParameterValue("OSC4PITCH");
            auto& detune4=*apvts.getRawParameterValue("OSC4DETUNE");
            
            auto& oscWaveChoice5=*apvts.getRawParameterValue("OSC5WAVETYPE");
            auto& fmFrequ5=*apvts.getRawParameterValue("OSC5FMFREQ");
            auto& fmDepth5=*apvts.getRawParameterValue("OSC5FMDEPTH");
            auto& lfoFrequ5=*apvts.getRawParameterValue("OSC5LFOFREQ");
            auto& lfoDepth5=*apvts.getRawParameterValue("OSC5LFODEPTH");
            auto& levelInDecibels5=*apvts.getRawParameterValue("OSC5GAIN");
            auto& oscPitch5=*apvts.getRawParameterValue("OSC5PITCH");
            auto& detune5=*apvts.getRawParameterValue("OSC5DETUNE");
            
            auto& oscWaveChoice6=*apvts.getRawParameterValue("OSC6WAVETYPE");
            auto& fmFrequ6=*apvts.getRawParameterValue("OSC6FMFREQ");
            auto& fmDepth6=*apvts.getRawParameterValue("OSC6FMDEPTH");
            auto& lfoFrequ6=*apvts.getRawParameterValue("OSC6LFOFREQ");
            auto& lfoDepth6=*apvts.getRawParameterValue("OSC6LFODEPTH");
            auto& levelInDecibels6=*apvts.getRawParameterValue("OSC6GAIN");
            auto& oscPitch6=*apvts.getRawParameterValue("OSC6PITCH");
            auto& detune6=*apvts.getRawParameterValue("OSC6DETUNE");
            
            auto& oscWaveChoice7=*apvts.getRawParameterValue("OSC7WAVETYPE");
            auto& fmFrequ7=*apvts.getRawParameterValue("OSC7FMFREQ");
            auto& fmDepth7=*apvts.getRawParameterValue("OSC7FMDEPTH");
            auto& lfoFrequ7=*apvts.getRawParameterValue("OSC7LFOFREQ");
            auto& lfoDepth7=*apvts.getRawParameterValue("OSC7LFODEPTH");
            auto& levelInDecibels7=*apvts.getRawParameterValue("OSC7GAIN");
            auto& oscPitch7=*apvts.getRawParameterValue("OSC7PITCH");
            auto& detune7=*apvts.getRawParameterValue("OSC7DETUNE");
            
            auto& oscWaveChoice8=*apvts.getRawParameterValue("OSC8WAVETYPE");
            auto& fmFrequ8=*apvts.getRawParameterValue("OSC8FMFREQ");
            auto& fmDepth8=*apvts.getRawParameterValue("OSC8FMDEPTH");
            auto& lfoFrequ8=*apvts.getRawParameterValue("OSC8LFOFREQ");
            auto& lfoDepth8=*apvts.getRawParameterValue("OSC8LFODEPTH");
            auto& levelInDecibels8=*apvts.getRawParameterValue("OSC8GAIN");
            auto& oscPitch8=*apvts.getRawParameterValue("OSC8PITCH");
            auto& detune8=*apvts.getRawParameterValue("OSC8DETUNE");
            
            auto& oscWaveChoice9=*apvts.getRawParameterValue("OSC9WAVETYPE");
            auto& fmFrequ9=*apvts.getRawParameterValue("OSC9FMFREQ");
            auto& fmDepth9=*apvts.getRawParameterValue("OSC9FMDEPTH");
            auto& lfoFrequ9=*apvts.getRawParameterValue("OSC9LFOFREQ");
            auto& lfoDepth9=*apvts.getRawParameterValue("OSC9LFODEPTH");
            auto& levelInDecibels9=*apvts.getRawParameterValue("OSC9GAIN");
            auto& oscPitch9=*apvts.getRawParameterValue("OSC9PITCH");
            auto& detune9=*apvts.getRawParameterValue("OSC9DETUNE");
            
            auto& oscWaveChoice10=*apvts.getRawParameterValue("OSC10WAVETYPE");
            auto& fmFrequ10=*apvts.getRawParameterValue("OSC10FMFREQ");
            auto& fmDepth10=*apvts.getRawParameterValue("OSC10FMDEPTH");
            auto& lfoFrequ10=*apvts.getRawParameterValue("OSC10LFOFREQ");
            auto& lfoDepth10=*apvts.getRawParameterValue("OSC10LFODEPTH");
            auto& levelInDecibels10=*apvts.getRawParameterValue("OSC10GAIN");
            auto& oscPitch10=*apvts.getRawParameterValue("OSC10PITCH");
            auto& detune10=*apvts.getRawParameterValue("OSC10DETUNE");
            
            for (int i = 0; i < 2; i++)
            {
                voice->getOscillator1()[i].setWaveType(oscWaveChoice1);
                voice->getOscillator1()[i].setFmParams(fmDepth1, fmFrequ1);
                voice->getOscillator1()[i].setLfoParams(lfoDepth1, lfoFrequ1);
                voice->getOscillator1()[i].setGain(levelInDecibels1);
                voice->getOscillator1()[i].setPitch(oscPitch1);
                voice->getOscillator1()[i].setDetuner(detune1);
                
                voice->getOscillator2()[i].setWaveType(oscWaveChoice2);
                voice->getOscillator2()[i].setFmParams(fmDepth2, fmFrequ2);
                voice->getOscillator2()[i].setLfoParams(lfoDepth2, lfoFrequ2);
                voice->getOscillator2()[i].setGain(levelInDecibels2);
                voice->getOscillator2()[i].setPitch(oscPitch2);
                voice->getOscillator2()[i].setDetuner(detune2);
                
                voice->getOscillator3()[i].setWaveType(oscWaveChoice3);
                voice->getOscillator3()[i].setFmParams(fmDepth3, fmFrequ3);
                voice->getOscillator3()[i].setLfoParams(lfoDepth3, lfoFrequ3);
                voice->getOscillator3()[i].setGain(levelInDecibels3);
                voice->getOscillator3()[i].setPitch(oscPitch3);
                voice->getOscillator3()[i].setDetuner(detune3);
                
                voice->getOscillator4()[i].setWaveType(oscWaveChoice4);
                voice->getOscillator4()[i].setFmParams(fmDepth4, fmFrequ4);
                voice->getOscillator4()[i].setLfoParams(lfoDepth4, lfoFrequ4);
                voice->getOscillator4()[i].setGain(levelInDecibels4);
                voice->getOscillator4()[i].setPitch(oscPitch4);
                voice->getOscillator4()[i].setDetuner(detune4);
                
                voice->getOscillator5()[i].setWaveType(oscWaveChoice5);
                voice->getOscillator5()[i].setFmParams(fmDepth5, fmFrequ5);
                voice->getOscillator5()[i].setLfoParams(lfoDepth5, lfoFrequ5);
                voice->getOscillator5()[i].setGain(levelInDecibels5);
                voice->getOscillator5()[i].setPitch(oscPitch5);
                voice->getOscillator5()[i].setDetuner(detune5);
                
                voice->getOscillator6()[i].setWaveType(oscWaveChoice6);
                voice->getOscillator6()[i].setFmParams(fmDepth6, fmFrequ6);
                voice->getOscillator6()[i].setLfoParams(lfoDepth6, lfoFrequ6);
                voice->getOscillator6()[i].setGain(levelInDecibels6);
                voice->getOscillator6()[i].setPitch(oscPitch6);
                voice->getOscillator6()[i].setDetuner(detune6);
                
                voice->getOscillator7()[i].setWaveType(oscWaveChoice7);
                voice->getOscillator7()[i].setFmParams(fmDepth7, fmFrequ7);
                voice->getOscillator7()[i].setLfoParams(lfoDepth7, lfoFrequ7);
                voice->getOscillator7()[i].setGain(levelInDecibels7);
                voice->getOscillator7()[i].setPitch(oscPitch7);
                voice->getOscillator7()[i].setDetuner(detune7);
                
                voice->getOscillator8()[i].setWaveType(oscWaveChoice8);
                voice->getOscillator8()[i].setFmParams(fmDepth8, fmFrequ8);
                voice->getOscillator8()[i].setLfoParams(lfoDepth8, lfoFrequ8);
                voice->getOscillator8()[i].setGain(levelInDecibels8);
                voice->getOscillator8()[i].setPitch(oscPitch8);
                voice->getOscillator8()[i].setDetuner(detune8);
                
                voice->getOscillator9()[i].setWaveType(oscWaveChoice9);
                voice->getOscillator9()[i].setFmParams(fmDepth9, fmFrequ9);
                voice->getOscillator9()[i].setLfoParams(lfoDepth9, lfoFrequ9);
                voice->getOscillator9()[i].setGain(levelInDecibels9);
                voice->getOscillator9()[i].setPitch(oscPitch9);
                voice->getOscillator9()[i].setDetuner(detune9);
                
                voice->getOscillator10()[i].setWaveType(oscWaveChoice10);
                voice->getOscillator10()[i].setFmParams(fmDepth10, fmFrequ10);
                voice->getOscillator10()[i].setLfoParams(lfoDepth10, lfoFrequ10);
                voice->getOscillator10()[i].setGain(levelInDecibels10);
                voice->getOscillator10()[i].setPitch(oscPitch10);
                voice->getOscillator10()[i].setDetuner(detune10);
            }
            
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
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC3WAVETYPE", "Osc 3 Wave Type", juce::StringArray {"Sine", "Saw", "Square"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC4WAVETYPE", "Osc 4 Wave Type", juce::StringArray {"Sine", "Saw", "Square"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC5WAVETYPE", "Osc 5 Wave Type", juce::StringArray {"Sine", "Saw", "Square"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC6WAVETYPE", "Osc 6 Wave Type", juce::StringArray {"Sine", "Saw", "Square"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC7WAVETYPE", "Osc 7 Wave Type", juce::StringArray {"Sine", "Saw", "Square"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC8WAVETYPE", "Osc 8 Wave Type", juce::StringArray {"Sine", "Saw", "Square"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC9WAVETYPE", "Osc 9 Wave Type", juce::StringArray {"Sine", "Saw", "Square"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC10WAVETYPE", "Osc 10 Wave Type", juce::StringArray {"Sine", "Saw", "Square"}, 0));
    
    //Gain
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC1GAIN", "Oscillator 1 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, -2.0f, "dB"));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC2GAIN", "Oscillator 2 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, -2.0f, "dB"));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC3GAIN", "Oscillator 3 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, -2.0f, "dB"));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC4GAIN", "Oscillator 4 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, -2.0f, "dB"));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC5GAIN", "Oscillator 5 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, -2.0f, "dB"));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC6GAIN", "Oscillator 6 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, -2.0f, "dB"));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC7GAIN", "Oscillator 7 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, -2.0f, "dB"));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC8GAIN", "Oscillator 8 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, -2.0f, "dB"));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC9GAIN", "Oscillator 9 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, -2.0f, "dB"));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("OSC10GAIN", "Oscillator 10 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, -2.0f, "dB"));
    
    //Pitch
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC1PITCH", "Oscillator 1 Pitch",  -48, 48, 0 ));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC2PITCH", "Oscillator 2 Pitch",  -48, 48, 0 ));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC3PITCH", "Oscillator 3 Pitch",  -48, 48, 0 ));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC4PITCH", "Oscillator 4 Pitch",  -48, 48, 0 ));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC5PITCH", "Oscillator 5 Pitch",  -48, 48, 0 ));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC6PITCH", "Oscillator 6 Pitch",  -48, 48, 0 ));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC7PITCH", "Oscillator 7 Pitch",  -48, 48, 0 ));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC8PITCH", "Oscillator 8 Pitch",  -48, 48, 0 ));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC9PITCH", "Oscillator 9 Pitch",  -48, 48, 0 ));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC10PITCH", "Oscillator 10 Pitch",  -48, 48, 0 ));

    
    //FM
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMFREQ","Osc 1 FM Frequency",juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMDEPTH","Osc 1 FM Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2FMFREQ","Osc 2 FM Frequency",juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2FMDEPTH","Osc 2 FM Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC3FMFREQ","Osc 3 FM Frequency",juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC3FMDEPTH","Osc 3 FM Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC4FMFREQ","Osc 4 FM Frequency",juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC4FMDEPTH","Osc 4 FM Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC5FMFREQ","Osc 5 FM Frequency",juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC5FMDEPTH","Osc 5 FM Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC6FMFREQ","Osc 6 FM Frequency",juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC6FMDEPTH","Osc 6 FM Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC7FMFREQ","Osc 7 FM Frequency",juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC7FMDEPTH","Osc 7 FM Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC8FMFREQ","Osc 8 FM Frequency",juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC8FMDEPTH","Osc 8 FM Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC9FMFREQ","Osc 9 FM Frequency",juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC9FMDEPTH","Osc 9 FM Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC10FMFREQ","Osc 10 FM Frequency",juce::NormalisableRange<float> {0.0f, 1000.0f, 0.01f, 0.3f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC10FMDEPTH","Osc 10 FM Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f, 0.3f},0.0f));
    
    //LFO
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1LFOFREQ","Osc 1 LFO Frequency",juce::NormalisableRange<float> {0.0f, 40.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1LFODEPTH","Osc 1 LFO Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2LFOFREQ","Osc 2 LFO Frequency",juce::NormalisableRange<float> {0.0f, 40.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2LFODEPTH","Osc 2 LFO Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC3LFOFREQ","Osc 3 LFO Frequency",juce::NormalisableRange<float> {0.0f, 40.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC3LFODEPTH","Osc 3 LFO Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC4LFOFREQ","Osc 4 LFO Frequency",juce::NormalisableRange<float> {0.0f, 40.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC4LFODEPTH","Osc 4 LFO Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC5LFOFREQ","Osc 5 LFO Frequency",juce::NormalisableRange<float> {0.0f, 40.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC5LFODEPTH","Osc 5 LFO Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC6LFOFREQ","Osc 6 LFO Frequency",juce::NormalisableRange<float> {0.0f, 40.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC6LFODEPTH","Osc 6 LFO Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC7LFOFREQ","Osc 7 LFO Frequency",juce::NormalisableRange<float> {0.0f, 40.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC7LFODEPTH","Osc 7 LFO Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC8LFOFREQ","Osc 8 LFO Frequency",juce::NormalisableRange<float> {0.0f, 40.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC8LFODEPTH","Osc 8 LFO Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC9LFOFREQ","Osc 9 LFO Frequency",juce::NormalisableRange<float> {0.0f, 40.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC9LFODEPTH","Osc 9 LFO Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f,},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC10LFOFREQ","Osc 10 LFO Frequency",juce::NormalisableRange<float> {0.0f, 40.0f, 0.01f},0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC10LFODEPTH","Osc 10 LFO Depth",juce::NormalisableRange<float> {0.0f, 100.0f, 0.01f},0.0f));
    
    //DETUNER
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1DETUNE", "Osc 1 Detuner",juce::NormalisableRange<float> {-30.0f, 30.0f, 0.01f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2DETUNE", "Osc 2 Detuner",juce::NormalisableRange<float> {-30.0f, 30.0f, 0.01f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC3DETUNE", "Osc 3 Detuner",juce::NormalisableRange<float> {-30.0f, 30.0f, 0.01f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC4DETUNE", "Osc 4 Detuner",juce::NormalisableRange<float> {-30.0f, 30.0f, 0.01f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC5DETUNE", "Osc 5 Detuner",juce::NormalisableRange<float> {-30.0f, 30.0f, 0.01f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC6DETUNE", "Osc 6 Detuner",juce::NormalisableRange<float> {-30.0f, 30.0f, 0.01f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC7DETUNE", "Osc 7 Detuner",juce::NormalisableRange<float> {-30.0f, 30.0f, 0.01f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC8DETUNE", "Osc 8 Detuner",juce::NormalisableRange<float> {-30.0f, 30.0f, 0.01f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC9DETUNE", "Osc 9 Detuner",juce::NormalisableRange<float> {-30.0f, 30.0f, 0.01f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC10DETUNE", "Osc 10 Detuner",juce::NormalisableRange<float> {-30.0f, 30.0f, 0.01f}, 0.0f));
    
    
    //ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK","Attack",juce::NormalisableRange<float> {0.1f, 1.0f},0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY","Decay",juce::NormalisableRange<float> {0.1f, 1.0f},0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN","Sustain",juce::NormalisableRange<float> {0.1f, 1.0f},1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE","Release",juce::NormalisableRange<float> {0.1f, 3.0f},0.4f));
    

    return {params.begin(), params.end()};
    
}

