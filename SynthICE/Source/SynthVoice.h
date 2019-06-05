/*
  ==============================================================================

    SynthVoice.h
    Created: 27 May 2019 5:46:24pm
    Author:  Said Sarabia Saavedra

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "DSP.h"
#include "Oscilloscope.h"

class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound(SynthesiserSound* sound)
    {
        return dynamic_cast<SynthesiserSound*>(sound) != nullptr;
    }
   
// ==============================================================================
    
    void getOscType (float* selection, float* lfoVal)
    {
        thewave = *selection;
        lfovalue = *lfoVal;
    }
    
    void getOscType2 (float* selection)
    {
        thewave2 = *selection;
    }
    
    void getOsc2Params (float* freq, float* blend)
    {
        osc2freq = *freq;
        osc2blend = *blend;
        
    }
    void getMixerParams (float* gain)
    {
        mixerGain = *gain;
    }
    
// ==============================================================================

    double setOscType()
    {
        double sample1, sample2, sample3;
        
        switch (thewave)
        {
            case 0:
                sample1 = osc1.sinewave(frequency);
                sample3 = LFO.sinewave(lfovalue);
                break;
            case 1:
                sample1 = osc1.saw(frequency);
                sample3 = LFO.saw(lfovalue);
                break;
            case 2:
                sample1 = osc1.trianglewave(frequency);
                sample3 = LFO.trianglewave(lfovalue);
                break;
            case 3:
                sample1 = osc1.squarewave(frequency);
                sample3 = LFO.squarewave(lfovalue);
                break;
            default:
                sample1 = osc1.sinewave(frequency);
                sample3 = LFO.sinewave(lfovalue);
                break;
        }
        
        switch (thewave2)
        {
            case 0:
                sample2 = osc2.sinewave(frequency+osc2freq);
                break;
            case 1:
                sample2 = osc2.saw(frequency+osc2freq);
                break;
            case 2:
                sample2 = osc2.trianglewave(frequency+osc2freq);
            case 3:
                sample2 = osc2.squarewave(frequency+osc2freq);
                break;
            default:
                sample2 = osc2.sinewave(frequency+osc2freq);
                break;
        }
        
        return (sample1+osc2blend*sample2)*sample3;
    }

// ==============================================================================

    void getEnvelopeParams(float* attack, float* decay, float* sustain, float* release)
    {
        env1.setAttack(*attack);
        env1.setDecay(*decay);
        env1.setSustain(*sustain);
        env1.setRelease(*release);
    }

// ==============================================================================
    
    double theSound()
    {
        return env1.adsr(setOscType(),env1.trigger);
    }
    
// ==============================================================================

    void getFilterParams(float* filterType, float* filterCutOff, float* filterRes)
    {
        filterChoice = *filterType;
        cutoff = *filterCutOff;
        resonance = *filterRes;
    }
    
// ==============================================================================
    
// ==============================================================================

    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        std::cout << frequency << std::endl;
        std::cout << osc2freq << std::endl;
    }
// ==============================================================================
    void stopNote (float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        allowTailOff = true;
        
        if (velocity == 0)
            clearCurrentNote();
    }
// ==============================================================================
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
// ==============================================================================
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }
// ==============================================================================
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {        
        for (int sample = 0; sample<numSamples; ++sample)
        {
            //double thewave = osc1.sinewave(frequency);
            //double thesound = env1.adsr(setOscType(),env1.trigger)*level;
            
            for (int channel = 0; channel<outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, theSound()*mixerGain);
            }
            ++startSample;
        }
       // scopeDataCollector.process(outputBuffer.getReadPointer(0), outputBuffer.getNumSamples());
    }
// ==============================================================================
    
private:
    //AudioBufferQueue<float> audioBufferQueue;
    //ScopeDataCollector<float> scopeDataCollector { audioBufferQueue };
    double level, frequency, velocity;
    
    int filterChoice;
    float cutoff, resonance, lfovalue, gain;
    
    float osc2freq, osc2blend, mixerGain;
    
    VCO osc1, osc2, LFO;
    Env env1;
    int thewave, thewave2;
    
};
