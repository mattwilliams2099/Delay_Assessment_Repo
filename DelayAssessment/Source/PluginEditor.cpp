#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayAssessmentAudioProcessorEditor::DelayAssessmentAudioProcessorEditor (DelayAssessmentAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState(vts)
{

    juce::Colour sliderColour = juce::Colours::darkslategrey;
    juce::Slider::SliderStyle sliderStyle = juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag;
    setSlider (delayTimeSlider,  sliderColour, sliderStyle);
    setSlider (feedbackSlider,   sliderColour, sliderStyle);
    setSlider (driveSlider,      sliderColour, sliderStyle);
    setSlider (trebleSlider,     sliderColour, sliderStyle);
    setSlider (bassSlider,       sliderColour, sliderStyle);
    setSlider (balanceSlider,    sliderColour, sliderStyle);
    setSlider (gainSlider,       sliderColour, sliderStyle);
    setSlider (panSlider,        sliderColour, sliderStyle);

    addAndMakeVisible (tap1Button);
    addAndMakeVisible (tap2Button);
    addAndMakeVisible (tap3Button);    

    setLabel (drive,     driveSlider,    "DRIVE");
    setLabel (speed,     delayTimeSlider,"SPEED\nCONTROL");
    setLabel (feedback,  feedbackSlider, "FEEDBACK\nCONTROL");
    setLabel (treble,    trebleSlider,   "TREBLE");
    setLabel (bass,      bassSlider,     "BASS");
    setLabel (balance,   balanceSlider,  "BALANCE");
    setLabel (pan,       panSlider,      "PAN");
    setLabel (gain,      gainSlider,     "GAIN");
    setLabel (tap,       tap1Button,     "TAP", false);
    setLabel (wet,       balanceSlider,  "WET", false);
    setLabel (dry,       balanceSlider,  "DRY", false);
    setLabel (min,       delayTimeSlider,"MIN", false);
    setLabel (max,       delayTimeSlider,"MAX", false);
    wet.setFont (8);
    dry.setFont (8);
    min.setFont (8);
    max.setFont (8);

    delayTimeAttachment = std::make_unique<SliderAttachment>    (valueTreeState, "DELAYTIME",   delayTimeSlider);
    feedbackAttachment = std::make_unique<SliderAttachment>     (valueTreeState, "FEEDBACK",    feedbackSlider);
    driveAttachment = std::make_unique<SliderAttachment>        (valueTreeState, "DRIVE",       driveSlider);
    trebleAttachment = std::make_unique<SliderAttachment>       (valueTreeState, "TREBLE",      trebleSlider);
    bassAttachment = std::make_unique<SliderAttachment>         (valueTreeState, "BASS",        bassSlider);
    balanceAttachment = std::make_unique<SliderAttachment>      (valueTreeState, "BALANCE",     balanceSlider);
    panAttachment = std::make_unique<SliderAttachment>          (valueTreeState, "PAN",         panSlider);
    gainAttachment = std::make_unique<SliderAttachment>         (valueTreeState, "GAIN",        gainSlider);
    tap1Attachment = std::make_unique<ButtonAttachment>         (valueTreeState, "TAP1",        tap1Button);
    tap2Attachment = std::make_unique<ButtonAttachment>         (valueTreeState, "TAP2",        tap2Button);
    tap3Attachment = std::make_unique<ButtonAttachment>         (valueTreeState, "TAP3",        tap3Button);

    setSize (400, 240);
}

DelayAssessmentAudioProcessorEditor::~DelayAssessmentAudioProcessorEditor()
{
}

//==============================================================================
void DelayAssessmentAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setGradientFill (juce::ColourGradient::ColourGradient(juce::Colours::slategrey, 150, 100, juce::Colours::darkslategrey, 400, 300, false));
    g.fillAll();
    g.setColour (juce::Colours::whitesmoke);
    g.drawVerticalLine (110, 25, 215);
    g.drawVerticalLine (225, 25, 215);
    g.drawRoundedRectangle (20, 20, 360, 200, 3, 2);
}

void DelayAssessmentAudioProcessorEditor::resized()
{
    //Input
    panSlider.setBounds         (25,  45,  85, 85);    
    driveSlider.setBounds       (25,  140, 85, 85);
    //Delay
    feedbackSlider.setBounds    (140, 45,  85, 85);
    delayTimeSlider.setBounds   (140, 140, 85, 85);
    tap1Button.setBounds        (115, 50,  20, 20);
    tap2Button.setBounds        (115, 110, 20, 20);
    tap3Button.setBounds        (115, 170, 20, 20);
    //Output
    trebleSlider.setBounds      (227, 47,  75, 75);
    bassSlider.setBounds        (307, 47,  75, 75);
    balanceSlider.setBounds     (222, 140, 85, 85);
    gainSlider.setBounds        (300, 140, 85, 85);

    tap.setBounds               (113, 25,  30, 20);
    dry.setBounds               (220, 204, 30, 20);
    wet.setBounds               (281, 204, 30, 20);
    min.setBounds               (137, 204, 30, 20);
    max.setBounds               (199, 204, 30, 20);



}

void DelayAssessmentAudioProcessorEditor::setSlider (juce::Slider& slider, juce::Colour colour, juce::Slider::SliderStyle style)
{
    addAndMakeVisible (slider);
    slider.setSliderStyle (style);
    slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 50, 10);

    slider.setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    slider.setColour (juce::Slider::thumbColourId, colour);
    slider.setColour (juce::Slider::backgroundColourId, juce::Colours::black);
    slider.setColour (juce::Slider::rotarySliderFillColourId, juce::Colours::black);
    slider.setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    slider.setColour (juce::Slider::trackColourId, juce::Colours::black);
}

void DelayAssessmentAudioProcessorEditor::setLabel (juce::Label& label, juce::Component& component, std::string name, bool attach)
{

    if (attach == true) label.attachToComponent (&component, false);
    label.setColour (juce::Label::textColourId, juce::Colours::whitesmoke);
    label.setText (name, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    label.setFont (10);
    addAndMakeVisible (label);
}