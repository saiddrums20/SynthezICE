/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SynthIceAudioProcessorEditor::SynthIceAudioProcessorEditor (SynthIceAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p), oscGUI(p),  osc2GUI(p), envGUI(p), filterGUI(p), scopeComponent(processor.getAudioBufferQueue()), mixerGUI(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (720, 405);
    BackgroundImage = ImageCache::getFromMemory(Images::newProject2_png, Images::newProject2_pngSize);
    
    
    addAndMakeVisible(&oscGUI);
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&filterGUI);
    addAndMakeVisible(scopeComponent);
    addAndMakeVisible(&osc2GUI);
    addAndMakeVisible(&mixerGUI);
}

SynthIceAudioProcessorEditor::~SynthIceAudioProcessorEditor()
{
}

//==============================================================================
void SynthIceAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (Colours::lightgrey);
    g.drawImage(BackgroundImage, 0, 0,720,405,0,0,720,405);

}

void SynthIceAudioProcessorEditor::resized()
{
    oscGUI.setBounds(36, 0, 100, 200);
    osc2GUI.setBounds(138, 0, 100, 200);
    envGUI.setBounds(240, 0, 100, 200);
    filterGUI.setBounds(342, 0, 150, 200);
    mixerGUI.setBounds(494, 0, 50, 200);
    scopeComponent.setBounds(546, 0, scopeComponent.getBounds().getWidth(), scopeComponent.getBounds().getHeight());
}


