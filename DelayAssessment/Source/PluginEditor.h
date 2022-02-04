#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

//==============================================================================
/**
*/
class DelayAssessmentAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DelayAssessmentAudioProcessorEditor (DelayAssessmentAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~DelayAssessmentAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::AudioProcessorValueTreeState& valueTreeState;
    DelayAssessmentAudioProcessor& audioProcessor;

    juce::Slider panSlider;
    juce::Slider driveSlider;
    juce::Slider feedbackSlider;
    juce::Slider delayTimeSlider;
    juce::Slider trebleSlider;
    juce::Slider bassSlider;
    juce::Slider balanceSlider;
    juce::Slider gainSlider;

    juce::ToggleButton tap1Button;
    juce::ToggleButton tap2Button;
    juce::ToggleButton tap3Button;

    std::unique_ptr<SliderAttachment> panAttachment;
    std::unique_ptr<SliderAttachment> driveAttachment;
    std::unique_ptr<SliderAttachment> feedbackAttachment;
    std::unique_ptr<SliderAttachment> delayTimeAttachment;
    std::unique_ptr<SliderAttachment> trebleAttachment;
    std::unique_ptr<SliderAttachment> bassAttachment;
    std::unique_ptr<SliderAttachment> balanceAttachment;
    std::unique_ptr<SliderAttachment> gainAttachment;
    std::unique_ptr<ButtonAttachment> tap1Attachment;
    std::unique_ptr<ButtonAttachment> tap2Attachment;
    std::unique_ptr<ButtonAttachment> tap3Attachment;

    juce::Label drive, speed, feedback, bass, treble, balance, pan, gain;
    juce::Label tap, wet, dry, min, max;

    void setSlider (juce::Slider& slider, juce::Colour colour, juce::Slider::SliderStyle style);
    void setLabel (juce::Label& label, juce::Component& component, std::string name, bool attach = true);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAssessmentAudioProcessorEditor)
};
