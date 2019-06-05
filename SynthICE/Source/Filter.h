/*
  ==============================================================================

    Filter.h
    Created: 1 Jun 2019 1:07:56pm
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
class Filter    : public Component
{
public:
    Filter(SynthIceAudioProcessor&);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;

private:
    Slider filterCutoff;
    Slider filterRes;
    Slider filterMenu;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterTypeVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resVal;
    
    Image filterImage;
    
    SynthIceAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
