/*
  ==============================================================================

    DelayClass.cpp
    Created: 19 Jan 2022 1:43:30pm
    Author:  mwill

  ==============================================================================
*/

#include "DelayClass.h"

DelayClass::DelayClass()
{
    bassFilter.setLowPassCo (2500, 0.5);
    trebleFilter.setHighPassCo (2500, 0.5);
    for (int j = 0; j < 2; j++)
    {
        wowLFO[j].setAmplitude     (150.0f);
        wowLFO[j].setFrequency     (0.1f);
        flutterLFO[j].setAmplitude (20.0f);
        flutterLFO[j].setFrequency (1.0f);
    }
    clearBuffer();
}

void DelayClass::writeBuffer (float audioSample, int channel)
{
    buffer [writeIndex [channel]] [(channel + 1) % 2] = softClip (- tapeFilter.filterProcess ((pan [channel] * (audioSample * drive)) + (feedback * readAllTaps (channel)), channel), 3);
    writeIndex [channel] ++;
    if (writeIndex [channel] == bufferLength)
        writeIndex [channel] = 0;
}

float DelayClass::readBuffer (int channel, int tap)
{

    rIndex[tap] = (writeIndex[channel] - delayTime[tap]) + applyWowFlutter (channel, tap);

    if (rIndex[tap] < 0)
        rIndex[tap] += bufferLength;
    else if (rIndex[tap] >= bufferLength)
        rIndex[tap] -= bufferLength;

    int rIndexTemp = static_cast<int> (rIndex[tap]);
    return linearInterpolate(buffer[rIndexTemp][channel], buffer[(rIndexTemp + 1) == bufferLength ? 0 : rIndexTemp + 1][channel], rIndex[tap]);

}

float DelayClass::applyWowFlutter (int channel, int tap)
{
    if (tap == 0)
    {
        wowLFO[channel].LFOIncrement();
        flutterLFO[channel].LFOIncrement();
    }
    return wowLFO[channel].getLFOOutput() + flutterLFO[channel].getLFOOutput();
}

void DelayClass::setDelayTime (float newValue)
{
    delayTime[0] = newValue;
    delayTime[1] = newValue / 2;
    delayTime[2] = newValue / 3;
    tapeFilter.setBandPassCo ((newValue - 1000) * -0.066f + 2000, 0.2f);
    wowLFO[0].setAmplitude (80 + (newValue * 0.003));
    wowLFO[1].setAmplitude (80 + (newValue * 0.003));
}

float DelayClass::delayProcess (float audioSample, int channel)
{
    writeBuffer (audioSample, channel);
    float crossover = (treble * trebleFilter.filterProcess (readAllTaps (channel), channel)) + (- bass * bassFilter.filterProcess (readAllTaps (channel), channel));
    return gain * ((dry * audioSample) + (wet * crossover));
}

void DelayClass::clearBuffer()
{
    for (int j = 0; j < numChannels; j++)
    {
        for (int i = 0; i < bufferLength; i++)
        {
            buffer[i][j] = 0;
        }
    }
}

float DelayClass::readAllTaps (int channel)
{
    return tap[0] * readBuffer (channel, 0) + tap[1] * readBuffer (channel, 1) + tap[2] * readBuffer (channel, 2);
}

void DelayClass::setBalance (float newValue)
{
    wet = newValue;
    dry = 1 - newValue;
}

void DelayClass::setPan (float newValue)
{
    pan[0] = linearPan (newValue);
    pan[1] = 1 - linearPan (newValue);
    pan[2] = newValue;
}