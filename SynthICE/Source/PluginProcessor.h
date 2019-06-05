/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "SynthVoice.h"
#include "Oscilloscope.h"


//==============================================================================
/**
*/
class SynthIceAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SynthIceAudioProcessor();
    ~SynthIceAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif
    
    void updateFilter();

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    AudioProcessorValueTreeState tree;
    AudioBufferQueue<float>& getAudioBufferQueue() noexcept  { return audioBufferQueue; }
    

private:
    Synthesiser mySynth;
    SynthVoice* myVoice;
    double lastSampleRate;
   AudioBufferQueue<float> audioBufferQueue;
    ScopeDataCollector<float> scopeDataCollector { audioBufferQueue };
    dsp::ProcessorDuplicator<dsp::StateVariableFilter::Filter <float> , dsp::StateVariableFilter::Parameters <float>> stateVariableFilter;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthIceAudioProcessor)
};
