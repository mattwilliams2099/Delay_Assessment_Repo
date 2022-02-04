
#include "LFOClass.h"

LFOClass::LFOClass (float samplefreq)
{
    sampleRate = samplefreq;
    samplePeriod = 1.0f / sampleRate;
    phase = 0;
}

void LFOClass::LFOIncrement()
{
    phase = phase + (2 * PI * frequency * samplePeriod);
    if (phase > 2 * PI)
            phase = phase - 2 * PI; 
    LFOOutput = amplitude * sin (phase);
}

void LFOClass::setSampleRate (float newValue) {
    sampleRate = newValue;
    samplePeriod = 1.0f / sampleRate;
}
