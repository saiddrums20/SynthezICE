/*
  ==============================================================================

    Mixer.h
    Created: 2 Jun 2019 5:56:41pm
    Author:  Said Sarabia Saavedra

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Images.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Mixer    : public Component
{
public:
    Mixer(SynthIceAudioProcessor&);
    ~Mixer();

    void paint (Graphics&) override;
    void resized() override;

private:
    Slider sliderVca;
    Image mixerImage;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> vcaVal;
    SynthIceAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mixer)
};
