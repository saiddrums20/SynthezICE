/*
  ==============================================================================

    Oscilator2.h
    Created: 1 Jun 2019 11:26:09pm
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
class Oscilator2    : public Component
{
public:
    Oscilator2(SynthIceAudioProcessor&);
    ~Oscilator2();

    void paint (Graphics&) override;
    void resized() override;

private:
    ComboBox osc2Menu;
    Slider frequencySlider;
    Slider blendSlider;
    Slider osc2Menu2;
    
    //ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection2;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> freqVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> blendVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> waveSelection2;
    
    Image osc2Image;
    
    SynthIceAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscilator2)
};
