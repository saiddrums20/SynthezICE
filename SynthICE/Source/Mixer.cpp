/*
  ==============================================================================

    Mixer.cpp
    Created: 2 Jun 2019 5:56:41pm
    Author:  Said Sarabia Saavedra

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Mixer.h"
#include "PluginProcessor.h"

//==============================================================================
Mixer::Mixer(SynthIceAudioProcessor& p) : processor(p)
{
    setSize(50, 200);
    
    mixerImage = ImageCache::getFromMemory(Images::newProject8_png, Images::newProject8_pngSize);
    
    sliderVca.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sliderVca.setRange(0, 1);
    sliderVca.setValue(0.3);
    sliderVca.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&sliderVca);
    
    vcaVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "mixerval", sliderVca);

}

Mixer::~Mixer()
{
}

void Mixer::paint (Graphics& g)
{

    g.drawImage(mixerImage, 0, 0,50,200,0,0,50,200);
}

void Mixer::resized()
{
    sliderVca.setBounds(5, 40, 40, 100);

}
