/*
  ==============================================================================

    SynthSound.h
    Created: 27 May 2019 5:46:17pm
    Author:  Said Sarabia Saavedra

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
public:
    bool appliesToNote(int /*midiNoteNumber*/)
    {
        return true;
    }
    bool appliesToChannel(int /*midiChannel*/)
    {
        return true;
    }
};
