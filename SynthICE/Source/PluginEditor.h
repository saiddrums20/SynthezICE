/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"
#include "Oscilator.h"
#include "Oscilator2.h"
#include "Envelope.h"
#include "Images.h"
#include "Filter.h"
#include "Oscilloscope.h"
#include "Mixer.h"

//==============================================================================
/**
*/
class SynthIceAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    SynthIceAudioProcessorEditor (SynthIceAudioProcessor&);
    ~SynthIceAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthIceAudioProcessor& processor;
    Oscilator oscGUI;
    Oscilator2 osc2GUI;
    Envelope envGUI;
    Filter filterGUI;
    ScopeComponent<float> scopeComponent;
    AudioBufferQueue<float> audioBufferQueue;
    ScopeDataCollector<float> scopeDataCollector { audioBufferQueue };
    Mixer mixerGUI;
    
    Slider attack;
    Image BackgroundImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthIceAudioProcessorEditor)
};
