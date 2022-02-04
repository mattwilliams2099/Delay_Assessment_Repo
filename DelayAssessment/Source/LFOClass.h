/*
  ==============================================================================

    LFOClass.h
    Created: 26 Jan 2022 3:16:14pm
    Author:  mwill

  ==============================================================================
*/

#pragma once
#include <cmath>
#define PI 3.14159265
class LFOClass
{
private:
    float frequency = 0;
    float phase = 0;
    float samplePeriod = 0;
    float LFOOutput = 0;
    float amplitude = 0;
    float sampleRate = 48000;
public:
    LFOClass (float samplefreq = 48000);
    void LFOIncrement();

    void setFrequency (float newValue) { frequency = newValue; }
    void setAmplitude (float newValue) { amplitude = newValue; }
    void setSampleRate (float newValue);

    float getFrequency() { return frequency; }
    float getAmplitude() { return amplitude; }

    float getLFOOutput() { return LFOOutput; }
};