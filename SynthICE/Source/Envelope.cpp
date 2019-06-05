/*
  ==============================================================================

    Envelope.cpp
    Created: 30 May 2019 1:01:29am
    Author:  Said Sarabia Saavedra

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(SynthIceAudioProcessor& p) : processor(p)
{
    setSize (100,200);
    //slider initialization values
    envImage = ImageCache::getFromMemory(Images::newProject6_png, Images::newProject6_pngSize);
    
    attackSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSlider.setRange(0.1f, 5000.0f);
    attackSlider.setValue(0.1f);
    attackSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&attackSlider);
    
    decaySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    decaySlider.setRange(1.0f, 2000.0f);
    decaySlider.setValue(1.0f);
    decaySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&decaySlider);
    
    sustainSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setValue(0.8f);
    sustainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&sustainSlider);
    
    releaseSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSlider.setRange(0.1f, 5000.0f);
    releaseSlider.setValue(0.8f);
    releaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&releaseSlider);
    
    //sends value of the sliders to the tree state in the processor
    attackVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "attack", attackSlider);
    decayVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "decay", decaySlider);
    sustainVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "sustain", sustainSlider);
    releaseVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "release", releaseSlider);

}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
    g.drawImage(envImage, 0, 0,100,200,0,0,100,200);
}

void Envelope::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    
    attackSlider.setBounds (1,20,50,50);
    decaySlider.setBounds (49,60,50,50);
    sustainSlider.setBounds (1,105,50,50);
    releaseSlider.setBounds (49,145,50,50);

}

