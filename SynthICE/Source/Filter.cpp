/*
  ==============================================================================

    Filter.cpp
    Created: 1 Jun 2019 1:07:56pm
    Author:  Said Sarabia Saavedra

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"
#include "PluginProcessor.h"

//==============================================================================
Filter::Filter(SynthIceAudioProcessor& p) : processor(p)
{
    setSize(150, 200);
    
    filterImage = ImageCache::getFromMemory(Images::newProject7_png, Images::newProject7_pngSize);
    
    filterMenu.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterMenu.setRange(0, 2, 1);
    filterMenu.setValue(0);
    filterMenu.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&filterMenu);
    filterTypeVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "filtertype", filterMenu);
    
    filterCutoff.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterCutoff.setRange(20.0, 20000.0);
    filterCutoff.setValue(400.0);
    filterCutoff.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&filterCutoff);
    filterVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filtercutoff", filterCutoff);
    filterCutoff.setSkewFactorFromMidPoint(1000.0);
    
    
    filterRes.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterRes.setRange(1.0, 5.0);
    filterRes.setValue(1.0);
    filterRes.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&filterRes);
    resVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "filterres", filterRes);
    
}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
    g.drawImage(filterImage, 0, 0,150,200,0,0,150,200);
}

void Filter::resized()
{
    filterCutoff.setBounds(28, 25, 95, 95);
    filterMenu.setBounds(18, 130, 60, 60);
    filterRes.setBounds(87, 135, 50, 50);
}
