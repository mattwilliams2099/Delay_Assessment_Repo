/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DelayClass.h"
#include "AudioUtilities.h"
#include <cmath>
//==============================================================================
/**
*/
class DelayAssessmentAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    DelayAssessmentAudioProcessor();
    ~DelayAssessmentAudioProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    DelayClass delay;
private:
    //==============================================================================
    juce::AudioProcessorValueTreeState parameters;
    std::atomic<float>* delayTimeParameter = nullptr;
    std::atomic<float>* feedbackParameter = nullptr;
    std::atomic<float>* driveParameter = nullptr;
    std::atomic<float>* bassParameter = nullptr;
    std::atomic<float>* trebleParameter = nullptr;
    std::atomic<float>* balanceParameter = nullptr;
    std::atomic<float>* tap1Parameter = nullptr;
    std::atomic<float>* tap2Parameter = nullptr;
    std::atomic<float>* tap3Parameter = nullptr;
    std::atomic<float>* panParameter = nullptr;
    std::atomic<float>* gainParameter = nullptr;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAssessmentAudioProcessor)
};
