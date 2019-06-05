/*
  ==============================================================================

    DSP.cpp
    Created: 28 May 2019 12:25:18pm
    Author:  Said Sarabia Saavedra

  ==============================================================================
*/

#include "DSP.h"
#include "math.h"

int Settings::sampleRate = 44100;
int Settings::channels = 2;
int Settings::bufferSize = 512;

void play(double *channels);

VCO::VCO()
{
    phase = 0.0;
}

double VCO::sinewave(double frequency)
{
    output = sin(phase*(TWOPI));
    if (phase > 2.0)
        phase -=2;
    phase += (1./(Settings::sampleRate/frequency));
    return(output);
}

double VCO::saw(double frequency)
{
    output=phase;
    if ( phase >= 1.0 ) phase -= 2.0;
    phase += (1./(Settings::sampleRate/(frequency)));
    return(output);
}

double VCO::squarewave(double frequency)
{
    if (phase<0.5) output=-1;
    if (phase>0.5) output=1;
    if ( phase >= 1.0 ) phase -= 1.0;
    phase += (1./(Settings::sampleRate/(frequency)));
    return(output);
}

double VCO::trianglewave(double frequency)
{
    if ( phase >= 1.0 ) phase -= 1.0;
    phase += (1./(Settings::sampleRate/(frequency)));
    if (phase <= 0.5 ) {
        output =(phase - 0.25) * 4;
    } else {
        output =((1.0-phase) - 0.25) * 4;
    }
    return(output);
}

double Env::adsr(double input, double attack, double decay, double sustain, double release, long holdtime, int trigger) {
    
    if (trigger==1 && attackphase!=1 && holdphase!=1 && decayphase!=1){
        holdcount=0;
        decayphase=0;
        sustainphase=0;
        releasephase=0;
        attackphase=1;
    }
    
    if (attackphase==1) {
        releasephase=0;
        amplitude+=(1*attack);
        output=input*amplitude;
        
        if (amplitude>=1) {
            amplitude=1;
            attackphase=0;
            decayphase=1;
        }
    }
    
    
    if (decayphase==1) {
        output=input*(amplitude*=decay);
        if (amplitude<=sustain) {
            decayphase=0;
            holdphase=1;
        }
    }
    
    if (holdcount<holdtime && holdphase==1) {
        output=input*amplitude;
        holdcount++;
    }
    
    if (holdcount>=holdtime && trigger==1) {
        output=input*amplitude;
    }
    
    if (holdcount>=holdtime && trigger!=1) {
        holdphase=0;
        releasephase=1;
    }
    
    if (releasephase==1 && amplitude>0.) {
        output=input*(amplitude*=release);
        
    }
    
    return output;
}

double Env::adsr(double input, int trigger) {
    
    if (trigger==1 && attackphase!=1 && holdphase!=1 && decayphase!=1){
        holdcount=0;
        decayphase=0;
        sustainphase=0;
        releasephase=0;
        attackphase=1;
    }
    
    if (attackphase==1) {
        releasephase=0;
        amplitude+=(1*attack);
        output=input*amplitude;
        
        if (amplitude>=1) {
            amplitude=1;
            attackphase=0;
            decayphase=1;
        }
    }
    
    
    if (decayphase==1) {
        output=input*(amplitude*=decay);
        if (amplitude<=sustain) {
            decayphase=0;
            holdphase=1;
        }
    }
    
    if (holdcount<holdtime && holdphase==1) {
        output=input*amplitude;
        holdcount++;
    }
    
    if (holdcount>=holdtime && trigger==1) {
        output=input*amplitude;
    }
    
    if (holdcount>=holdtime && trigger!=1) {
        holdphase=0;
        releasephase=1;
    }
    
    if (releasephase==1 && amplitude>0.) {
        output=input*(amplitude*=release);
        
    }
    
    return output;
}

void Env::setAttack(double attackMS) {
    attack = 1-pow( 0.01, 1.0 / ( attackMS * Settings::sampleRate * 0.001 ) );
}

void Env::setRelease(double releaseMS) {
    release = pow( 0.01, 1.0 / ( releaseMS * Settings::sampleRate * 0.001 ) );
}

void Env::setSustain(double sustainL) {
    sustain = sustainL;
}

void Env::setDecay(double decayMS) {
    decay = pow( 0.01, 1.0 / ( decayMS * Settings::sampleRate * 0.001 ) );
}
