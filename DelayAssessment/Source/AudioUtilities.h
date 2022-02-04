#pragma once
#include <cmath>

inline float parameterSmooth (float input, float previousInput, float alpha = 0.9)
{
    return (1.0f - alpha) * input + alpha * previousInput;
}

inline float linearInterpolate (float lowerBound, float upperBound, float fraction)
{
    int intFraction = fraction;
    float frac = fraction - intFraction;
    return ((1 - frac) * lowerBound) + (frac * upperBound);
}

inline float cubicInterpolate (float x2, float x1, float x, float x_1, float fraction)
{
    float a0 = x2 - x1 - x_1 + x;
    float a1 = x_1 - x - a0;
    float a2 = x1 - x_1;
    float a3 = x;
    fraction = fraction - floor (fraction);
    return a0 * powf (fraction, 3) + a1 * powf (fraction, 2) + a2 * fraction + a3;
}

inline float softClip (float input, float alpha = 3)
{
    return (0.9 / atan (alpha)) * atan (alpha * input);
}

inline float linearPan (float panValue)
{
    return panValue / 200 + 0.5;
}