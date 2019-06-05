/*
  ==============================================================================

    Oscilator.h
    Created: 29 May 2019 10:58:51pm
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
class Oscilator    : public Component, private ComboBox::Listener
{
public:
    Oscilator(SynthIceAudioProcessor&);
    ~Oscilator();

    void paint (Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(ComboBox*) override;

private:
    Slider oscMenu;
    Slider oscLFO;
    Image Osc1Image;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> waveSelection;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lfoSelection;
    SynthIceAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscilator)
};
