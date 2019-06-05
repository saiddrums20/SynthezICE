/*
  ==============================================================================

    DSP.h
    Created: 28 May 2019 12:25:25pm
    Author:  Said Sarabia Saavedra

  ==============================================================================
*/

#pragma once
#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif
#define TWOPI 6.283185307179586476925286766559

class Settings
{
public:
    static int sampleRate;
    static int channels;
    static int bufferSize;
    static void setup(int initSampleRate, int initChannels, int initBufferSize)
    {
        Settings::sampleRate = initSampleRate;
        Settings::channels = initChannels;
        Settings::bufferSize = initBufferSize;
    }
};

class VCO {
    double frequency;
    double phase;
    double startphase;
    double endphase;
    double output;
    double tri;
    
public:
    VCO();
    double sinewave(double frequency);
    double saw(double frequency);
    double squarewave(double frequency);
    double trianglewave(double frequency);
};

class Env {
public:
    double adsr(double input, double attack=1, double decay=0.99, double sustain=0.125, double release=0.9, long holdtime=1, int trigger=0);
    double adsr(double input,int trigger);
    double input;
    double output;
    double attack;
    double decay;
    double sustain;
    double release;
    double amplitude;
    void setAttack(double attackMS);
    void setRelease(double releaseMS);
    void setDecay(double decayMS);
    void setSustain(double sustainL);
    int trigger;
    long holdtime=1;
    long holdcount;
    int attackphase,decayphase,sustainphase,holdphase,releasephase;
};
