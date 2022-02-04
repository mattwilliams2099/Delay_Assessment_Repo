/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayAssessmentAudioProcessor::DelayAssessmentAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr, juce::Identifier ("delayValueTree"),
                           {
                                std::make_unique<juce::AudioParameterFloat> ("PAN",         "Pan",      -100.0f, 100.0f, 0.0f),
                                std::make_unique<juce::AudioParameterFloat> ("DRIVE",       "Drive",     0.0f,   2.0f,   1.0f),
                                std::make_unique<juce::AudioParameterFloat> ("FEEDBACK",    "Feedback",  0.0f,   0.8f,   0.4f),
                                std::make_unique<juce::AudioParameterBool>  ("TAP1",        "Tap 1", false),
                                std::make_unique<juce::AudioParameterBool>  ("TAP2",        "Tap 2", false),
                                std::make_unique<juce::AudioParameterBool>  ("TAP3",        "Tap 3", false),
                                std::make_unique<juce::AudioParameterInt>   ("DELAYTIME",   "Delay Time",3000,   29000,  20000),
                                std::make_unique<juce::AudioParameterFloat> ("TREBLE",      "Treble",    0.0f,   2.0f,   1.0f), 
                                std::make_unique<juce::AudioParameterFloat> ("BASS",        "Bass",      0.0f,   2.0f,   1.0f),
                                std::make_unique<juce::AudioParameterFloat> ("BALANCE",     "Balance",   0.0f,   1.0f,   0.5f),
                                std::make_unique<juce::AudioParameterFloat> ("GAIN",        "Gain",      0.0f,   2.0f,   1.0f)
                           })
#endif
{
    panParameter = parameters.getRawParameterValue ("PAN");
    driveParameter = parameters.getRawParameterValue ("DRIVE");
    tap1Parameter = parameters.getRawParameterValue ("TAP1");
    tap2Parameter = parameters.getRawParameterValue ("TAP2");
    tap3Parameter = parameters.getRawParameterValue ("TAP3");
    feedbackParameter = parameters.getRawParameterValue ("FEEDBACK");
    delayTimeParameter = parameters.getRawParameterValue ("DELAYTIME");
    trebleParameter = parameters.getRawParameterValue ("TREBLE");
    bassParameter = parameters.getRawParameterValue ("BASS");
    balanceParameter = parameters.getRawParameterValue ("BALANCE");
    gainParameter = parameters.getRawParameterValue ("GAIN");
}

DelayAssessmentAudioProcessor::~DelayAssessmentAudioProcessor()
{
}

//==============================================================================
const juce::String DelayAssessmentAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DelayAssessmentAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DelayAssessmentAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DelayAssessmentAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DelayAssessmentAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DelayAssessmentAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DelayAssessmentAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DelayAssessmentAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DelayAssessmentAudioProcessor::getProgramName (int index)
{
    return {};
}

void DelayAssessmentAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DelayAssessmentAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    delay.clearBuffer();

    delay.setPan (*panParameter);
    delay.setDrive (*driveParameter);
    delay.setFeedback (*feedbackParameter);
    delay.setDelayTime (32000 - *delayTimeParameter);
    delay.setTap1 (*tap1Parameter);
    delay.setTap2 (*tap2Parameter);
    delay.setTap3 (*tap3Parameter);
    delay.setTreble (*trebleParameter);
    delay.setBass (*bassParameter);
    delay.setBalance (*balanceParameter);
    delay.setGain (*gainParameter);
}

void DelayAssessmentAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DelayAssessmentAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DelayAssessmentAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    delay.setPan        (parameterSmooth    (*panParameter,     delay.getPan(),     0.9f));
    delay.setDrive      (parameterSmooth    (*driveParameter,   delay.getDrive(),   0.9f));
    delay.setFeedback   (parameterSmooth    (*feedbackParameter,delay.getFeedback(),0.9f));
    delay.setBass       (parameterSmooth    (*bassParameter,    delay.getBass(),    0.9f));
    delay.setTreble     (parameterSmooth    (*trebleParameter,  delay.getTreble(),  0.9f));
    delay.setBalance    (parameterSmooth    (*balanceParameter, delay.getBalance(), 0.9f));
    delay.setGain       (parameterSmooth    (*gainParameter,    delay.getGain(),    0.9f));
    delay.setTap1 (*tap1Parameter);
    delay.setTap2 (*tap2Parameter);
    delay.setTap3 (*tap3Parameter);

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            delay.setDelayTime(parameterSmooth(32000 - *delayTimeParameter, delay.getDelayTime(), 0.9995));
            channelData[sample] = delay.delayProcess(channelData[sample], channel);
        }
    }
}

//==============================================================================
bool DelayAssessmentAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DelayAssessmentAudioProcessor::createEditor()
{
    return new DelayAssessmentAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void DelayAssessmentAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void DelayAssessmentAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DelayAssessmentAudioProcessor();
}
