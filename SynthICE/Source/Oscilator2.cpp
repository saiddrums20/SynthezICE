/*
  ==============================================================================

    Oscilator2.cpp
    Created: 1 Jun 2019 11:26:09pm
    Author:  Said Sarabia Saavedra

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscilator2.h"

//==============================================================================
Oscilator2::Oscilator2(SynthIceAudioProcessor& p) : processor(p)
{
    setSize(100, 200);
    /*osc2Menu.addItem("Sine", 1);
    osc2Menu.addItem("Saw", 2);
    osc2Menu.addItem("Square", 3);
    osc2Menu.addItem("Triangular", 4);
    osc2Menu.setJustificationType(Justification::centred);
    addAndMakeVisible(&osc2Menu);*/
    osc2Image = ImageCache::getFromMemory(Images::newProject5_png, Images::newProject5_pngSize);
    
    osc2Menu2.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    osc2Menu2.setRange(0, 3, 1);
    osc2Menu2.setValue(0);
    osc2Menu2.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&osc2Menu2);
    waveSelection2 = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "wavetype2", osc2Menu2);
    
    frequencySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    frequencySlider.setRange(0, 32, 2);
    frequencySlider.setValue(2);
    frequencySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&frequencySlider);
    freqVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "osc2freq", frequencySlider);
    
    blendSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    blendSlider.setRange(0, 1);
    blendSlider.setValue(1);
    blendSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    addAndMakeVisible(&blendSlider);
    blendVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "blend", blendSlider);

}

Oscilator2::~Oscilator2()
{
}

void Oscilator2::paint (Graphics& g)
{
    g.drawImage(osc2Image, 0, 0,100,200,0,0,100,200);
}

void Oscilator2::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(40);
    osc2Menu2.setBounds(15, 20, 70, 70);
    frequencySlider.setBounds(47, 95, 50, 50);
    blendSlider.setBounds(47, 145, 50, 50);
}
