/*
  ==============================================================================

    Envelope.h
    Created: 30 May 2019 1:01:29am
    Author:  Said Sarabia Saavedra

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Images.h"

//==============================================================================
/*
*/
class Envelope    : public Component
{
public:
    Envelope(SynthIceAudioProcessor&);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;

private:
    Slider attackSlider;
    Slider decaySlider;
    Slider sustainSlider;
    Slider releaseSlider;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseVal;
    
    Image envImage;
    SynthIceAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
