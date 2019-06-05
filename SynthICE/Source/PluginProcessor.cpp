/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SynthIceAudioProcessor::SynthIceAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr, "Parameters",
                               {
                                   std::make_unique<AudioParameterFloat>("attack", "Attack", NormalisableRange<float>(0.1f, 5000.0f), 0.1f),
                                   std::make_unique<AudioParameterFloat>("decay", "Decay", NormalisableRange<float>(1.0f, 2000.0f), 1.0f),
                                   std::make_unique<AudioParameterFloat>("sustain", "Sustain", NormalisableRange<float>(0.0f, 1.0f), 0.8f),
                                   std::make_unique<AudioParameterFloat>("release", "Release", NormalisableRange<float>(0.1f, 5000.0f), 0.1f),
                                   std::make_unique<AudioParameterFloat>("wavetype", "WaveType", NormalisableRange<float>(0.0f,3.0f, 1.0f),0.0f),
                                   std::make_unique<AudioParameterFloat>("lfofreq", "LFOFreq", NormalisableRange<float>(0.0f, 32.0f, 2.0f),2.0f),
                                   std::make_unique<AudioParameterFloat>("filtertype", "FilterType", NormalisableRange<float>(0.0f,2.0f, 1.0f),0.0f),
                                   std::make_unique<AudioParameterFloat>("filtercutoff", "filterCutOff", NormalisableRange<float> (20.0f, 20000.0f), 400.0f),
                                   std::make_unique<AudioParameterFloat>("filterres", "FilterRes", NormalisableRange<float> (1.0f, 5.0f), 1.0f),
                                   std::make_unique<AudioParameterFloat>("wavetype2", "WaveType2", NormalisableRange<float>(0.0f, 3.0f, 1.0f), 0.0f),
                                   std::make_unique<AudioParameterFloat>("osc2freq", "Osc2Freq", NormalisableRange<float>(0.0f, 32.0f, 2.0f),2.0f),
                                   std::make_unique<AudioParameterFloat>("blend", "Osc2Blend",NormalisableRange<float>(0.0f, 1.0f), 1.0f),
                                   std::make_unique<AudioParameterFloat>("mixerval","MixerVal",NormalisableRange<float>(0.0f,1.0f),0.3f),
                               })
#endif
{
    mySynth.clearVoices();
    
    for (int i = 0; i<5; i++)
    {
        mySynth.addVoice(new SynthVoice());
    }
    
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

SynthIceAudioProcessor::~SynthIceAudioProcessor()
{
}

//==============================================================================
const String SynthIceAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthIceAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthIceAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthIceAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthIceAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthIceAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthIceAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthIceAudioProcessor::setCurrentProgram (int index)
{
}

const String SynthIceAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthIceAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SynthIceAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    stateVariableFilter.reset();
    stateVariableFilter.prepare(spec);
    updateFilter();
}

void SynthIceAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthIceAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void SynthIceAudioProcessor::updateFilter()
{
    int menuChoice = *tree.getRawParameterValue("filtertype");
    int freq = *tree.getRawParameterValue("filtercutoff");
    int res = *tree.getRawParameterValue("filterres");
    
    if (menuChoice == 0)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
    }
    
    if (menuChoice == 1)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
    }
    
    if (menuChoice == 2)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, freq, res);
    }
}

void SynthIceAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        //if myVoice sucessfully casts as a SynthVoice*, get the voice and set the params
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            myVoice->getEnvelopeParams(tree.getRawParameterValue("attack"),
                                       tree.getRawParameterValue("decay"),
                                       tree.getRawParameterValue("sustain"),
                                       tree.getRawParameterValue("release"));
            
            myVoice->getOscType(tree.getRawParameterValue("wavetype"), tree.getRawParameterValue("lfofreq"));
            myVoice->getOscType2(tree.getRawParameterValue("wavetype2"));
            
            myVoice->getFilterParams(tree.getRawParameterValue("filtertype"),tree.getRawParameterValue("filtercutoff"),tree.getRawParameterValue("filterres"));
            myVoice->getOsc2Params(tree.getRawParameterValue("osc2freq"),tree.getRawParameterValue("blend"));
            myVoice->getMixerParams(tree.getRawParameterValue("mixerval"));
        }
    }
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    updateFilter();
    dsp::AudioBlock<float> block (buffer);
    stateVariableFilter.process(dsp::ProcessContextReplacing<float> (block));
    scopeDataCollector.process(buffer.getReadPointer(0), buffer.getNumSamples());
}

//==============================================================================
bool SynthIceAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SynthIceAudioProcessor::createEditor()
{
    return new SynthIceAudioProcessorEditor (*this);
}

//==============================================================================
void SynthIceAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthIceAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthIceAudioProcessor();
}

