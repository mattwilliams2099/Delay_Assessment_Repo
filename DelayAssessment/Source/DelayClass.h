/*
  ==============================================================================

    DelayClass.h
    Created: 19 Jan 2022 1:43:30pm
    Author:  mwill

  ==============================================================================
*/

#pragma once

#include <cmath>
#include "AudioUtilities.h"
#include "FilterClass.h"
#include "LFOClass.h"

class DelayClass
{
private:
    const int bufferLength = 32000;
    const int numChannels = 2;
    const int numTaps = 3;

    float buffer[32000][2];
    float sampleRate = 48000;

    int writeIndex[2] = { 0, 0 };
    float rIndex[3] = { 0, 0, 0 };

    float pan[3];
    float drive;
    int tap[3];
    float feedback;
    float delayTime[3] = { 0, 0, 0 };
    float treble;
    float bass;
    float wet;
    float dry;
    float gain;

    FilterClass tapeFilter;
    FilterClass trebleFilter; 
    FilterClass bassFilter;

    LFOClass wowLFO [2];
    LFOClass flutterLFO [2];

    void writeBuffer (float audioSample, int channel);
    float readBuffer (int channel, int tap);
    float readAllTaps (int channel);
    float applyWowFlutter (int channel, int tap = 0);

public:
    DelayClass();

    void setSampleRate (float newValue) { sampleRate = newValue; }

    void setPan (float newValue);
    void setDrive (float newValue)      { drive = newValue; }
    void setTap1 (int newValue)         { tap [0] = newValue; }
    void setTap2 (int newValue)         { tap [1] = newValue; }
    void setTap3 (int newValue)         { tap [2] = newValue; }
    void setFeedback (float newValue)   { feedback = newValue; }
    void setDelayTime (float newValue);
    void setTreble (float newValue)     { treble = newValue; }
    void setBass (float newValue)       { bass = newValue; }
    void setBalance(float newValue);
    void setGain (float newValue)       { gain = newValue; }

    float getPan()                      { return pan [2]; }
    float getDrive()                    { return drive; }
    float getFeedback()                 { return feedback; }
    float getTreble()                   { return treble; }
    float getBass()                     { return bass; }
    float getGain()                     { return gain; }
    float getBalance()                  { return wet; }
    float getDelayTime()                { return delayTime [0]; }

    float delayProcess (float audioSample, int channel);

    void clearBuffer();
};

