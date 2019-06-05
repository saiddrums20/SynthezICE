/*
  ==============================================================================

    Oscilator.cpp
    Created: 29 May 2019 10:58:51pm
    Author:  Said Sarabia Saavedra

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscilator.h"

//==============================================================================
Oscilator::Oscilator(SynthIceAudioProcessor& p) : processor(p)
{
    setSize(100, 200);
    Osc1Image = ImageCache::getFromMemory(Images::newProject4_png, Images::newProject4_pngSize);
    
    oscMenu.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    oscMenu.setRange(0, 3, 1);
    oscMenu.setValue(0);
    oscMenu.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&oscMenu);
    waveSelection = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "wavetype", oscMenu);
    
    oscLFO.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    oscLFO.setRange(0, 32, 2);
    oscLFO.setValue(2);
    oscLFO.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&oscLFO);
    lfoSelection = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "lfofreq", oscLFO);
    
}

Oscilator::~Oscilator()
{
}

void Oscilator::paint (Graphics& g)
{
    g.drawImage(Osc1Image, 0, 0,100,200,0,0,100,200);
}

void Oscilator::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    oscMenu.setBounds(15, 20, 70, 70);
    oscLFO.setBounds(15, 115, 70, 70);
}

void Oscilator::comboBoxChanged(ComboBox* box)
{
    
}
