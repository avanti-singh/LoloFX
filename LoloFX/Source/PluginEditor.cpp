#include "PluginEditor.h"
#include "PluginProcessor.h"

PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    // Load background image
    backgroundImage = juce::ImageCache::getFromFile(
        juce::File("/Users/apple/Desktop/Fall24/EP353-ProblemSets/FinalProject/LoloFX/Resources/Images/BG2.png"));

    // Set custom LookAndFeel
    customLookAndFeel = std::make_unique<CustomLookAndFeel>();
    thresholdSlider.setLookAndFeel(customLookAndFeel.get());
    driveSlider.setLookAndFeel(customLookAndFeel.get());
    cutoffSlider.setLookAndFeel(customLookAndFeel.get());
    wetDrySlider.setLookAndFeel(customLookAndFeel.get());
    softclipButton.setLookAndFeel(customLookAndFeel.get());
    tapesaturationButton.setLookAndFeel(customLookAndFeel.get());
    waveshapeButton.setLookAndFeel(customLookAndFeel.get());
    rainButton.setLookAndFeel(customLookAndFeel.get());
    vinylButton.setLookAndFeel(customLookAndFeel.get());
    volumeslider.setLookAndFeel(customLookAndFeel.get());

    // Plugin name label
    addAndMakeVisible(pluginname);
    pluginname.setText("LoloFX", juce::dontSendNotification);
    pluginname.setFont(juce::Font("Helvetica", 30.0f, juce::Font::bold));
    pluginname.setJustificationType(juce::Justification::centred);

    // Saturator label
    addAndMakeVisible(saturatorlabel);
    saturatorlabel.setText("Saturator", juce::dontSendNotification);
    saturatorlabel.setFont(juce::Font("Helvetica", 20.0f, juce::Font::bold));
    saturatorlabel.setJustificationType(juce::Justification::centred);

    // Low-pass filter label
    addAndMakeVisible(lpflabel);
    lpflabel.setText("Low-Pass Filter", juce::dontSendNotification);
    lpflabel.setFont(juce::Font("Helvetica", 20.0f, juce::Font::bold));
    lpflabel.setJustificationType(juce::Justification::centred);

    // Add labels for sliders
    addAndMakeVisible(thresholdlabel);
    thresholdlabel.setText("Threshold", juce::dontSendNotification);
    thresholdlabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(drivelabel);
    drivelabel.setText("Drive", juce::dontSendNotification);
    drivelabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(wetdrylabel);
    wetdrylabel.setText("Wet/Dry Mix", juce::dontSendNotification);
    wetdrylabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(cutofflabel);
    cutofflabel.setText("Cutoff Frequency", juce::dontSendNotification);
    cutofflabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(samplelabel);
    samplelabel.setText("Sample", juce::dontSendNotification);
    samplelabel.setFont(juce::Font("Helvetica", 20.0f, juce::Font::bold));
    samplelabel.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(volumelabel);
    volumelabel.setText("Sample", juce::dontSendNotification);
    volumelabel.setJustificationType(juce::Justification::centred);

    // Input gain slider
    addAndMakeVisible(inputGainSlider);
    inputGainSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    inputGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "inputGain", inputGainSlider);

    // Output gain slider
    addAndMakeVisible(outputGainSlider);
    outputGainSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    outputGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "outputGain", outputGainSlider);

    // Saturator buttons
    auto setupButton = [this](juce::TextButton& button, const juce::String& text, int mode)
    {
        addAndMakeVisible(button);
        button.setButtonText(text);
        button.setClickingTogglesState(false); // Ensures toggle state is handled manually
        button.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
        button.setColour(juce::TextButton::buttonOnColourId, juce::Colours::blue);
        button.onClick = [this, &button, mode]
        {
            processor.parameters.getParameterAsValue("saturationMode").setValue(mode);

            // Set toggle state based on clicked button
            softclipButton.setToggleState(&button == &softclipButton, juce::dontSendNotification);
            tapesaturationButton.setToggleState(&button == &tapesaturationButton, juce::dontSendNotification);
            waveshapeButton.setToggleState(&button == &waveshapeButton, juce::dontSendNotification);
        };
    };

    setupButton(softclipButton, "Soft Clip", 0);
    setupButton(tapesaturationButton, "Tape Saturation", 1);
    setupButton(waveshapeButton, "Wave Shape", 2);

    // Sample Playback Buttons
    addAndMakeVisible(sampleonButton);
    sampleonButton.setButtonText("Play Sample");
    sampleonButton.setClickingTogglesState(true);
    sampleonButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::green);
    sampleonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
    processor.parameters, "playState", sampleonButton);

    addAndMakeVisible(rainButton);
    rainButton.setButtonText("Rain");
    rainButton.setClickingTogglesState(true);

    addAndMakeVisible(vinylButton);
    vinylButton.setClickingTogglesState(true);
    vinylButton.setButtonText("Vinyl");

    rainButton.onClick = [this]()
    {
        processor.parameters.getParameterAsValue("sound").setValue(0); // 0 corresponds to Rain
    };

    vinylButton.onClick = [this]()
    {
        processor.parameters.getParameterAsValue("sound").setValue(1); // 1 corresponds to Vinyl
    };

    setupButton(rainButton, "Rain", 0);
    setupButton(vinylButton, "Vinyl", 1);

    // Saturator sliders
    addAndMakeVisible(thresholdSlider);
    thresholdSlider.setSliderStyle(juce::Slider::Rotary);
    thresholdSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    thresholdSlider.setTextValueSuffix(" dB");
    saturationTHAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "threshold", thresholdSlider);

    addAndMakeVisible(driveSlider);
    driveSlider.setSliderStyle(juce::Slider::Rotary);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    driveSlider.setTextValueSuffix(" dB");
    saturationDRAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "drive", driveSlider);

    addAndMakeVisible(wetDrySlider);
    wetDrySlider.setSliderStyle(juce::Slider::Rotary);
    wetDrySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    wetDrySlider.setTextValueSuffix(" Mix");
    wetDryAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "wetDryMix", wetDrySlider);

    // Low-pass filter slider
    addAndMakeVisible(cutoffSlider);
    cutoffSlider.setSliderStyle(juce::Slider::Rotary);
    cutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    cutoffSlider.setSkewFactorFromMidPoint(1000.0f);
    cutoffSlider.setTextValueSuffix(" Hz");
    cutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "cutoffFrequency", cutoffSlider);

    //Sample Volume Slider
    addAndMakeVisible(volumeslider);
    volumeslider.setSliderStyle(juce::Slider::Rotary);
    volumeslider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    volumeslider.setTextValueSuffix(" dB");
    volumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "volume", volumeslider);

    setSize(700, 500);
}

PluginEditor::~PluginEditor()
{
    // Remove Listeners for Buttons
    rainButton.removeListener(this);
    vinylButton.removeListener(this);

    // Clear Custom LookAndFeel Assignments
    thresholdSlider.setLookAndFeel(nullptr);
    driveSlider.setLookAndFeel(nullptr);
    cutoffSlider.setLookAndFeel(nullptr);
    wetDrySlider.setLookAndFeel(nullptr);
    volumeslider.setLookAndFeel(nullptr);

    softclipButton.setLookAndFeel(nullptr);
    tapesaturationButton.setLookAndFeel(nullptr);
    waveshapeButton.setLookAndFeel(nullptr);
    rainButton.setLookAndFeel(nullptr);
    vinylButton.setLookAndFeel(nullptr);
}

void PluginEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    // Draw background image
    if (backgroundImage.isValid())
    {
        g.drawImageWithin(backgroundImage, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    }
}

void PluginEditor::resized()
{
    auto bounds = getLocalBounds();

    // Plugin title
    pluginname.setBounds(bounds.removeFromTop(60));

    // Input and output gain sliders
    auto centerArea = bounds.reduced(10);
    inputGainSlider.setBounds(centerArea.removeFromLeft(50).reduced(10));
    outputGainSlider.setBounds(centerArea.removeFromRight(50).reduced(10));

    // Saturator area
    auto saturatorArea = centerArea.removeFromTop(180);
    saturatorlabel.setBounds(saturatorArea.removeFromTop(5).withSizeKeepingCentre(200, 20));

    // Saturator mode buttons
    auto saturatorButtonArea = saturatorArea.removeFromTop(40);
    softclipButton.setBounds(saturatorButtonArea.removeFromLeft(saturatorButtonArea.getWidth() / 3).reduced(10));
    tapesaturationButton.setBounds(saturatorButtonArea.removeFromLeft(saturatorButtonArea.getWidth() / 2).reduced(10));
    waveshapeButton.setBounds(saturatorButtonArea.reduced(10));

    // Horizontal layout for saturator sliders
    auto sliderArea = saturatorArea.reduced(10);
    int sliderWidth = sliderArea.getWidth() / 3;

    thresholdSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).withSizeKeepingCentre(150, 150));
    driveSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).withSizeKeepingCentre(150, 150));
    wetDrySlider.setBounds(sliderArea.withSizeKeepingCentre(150, 150));

    // Labels for sliders
    thresholdlabel.setBounds(thresholdSlider.getX(), thresholdSlider.getBottom() + 5, thresholdSlider.getWidth(), 20);
    drivelabel.setBounds(driveSlider.getX(), driveSlider.getBottom() + 5, driveSlider.getWidth(), 20);
    wetdrylabel.setBounds(wetDrySlider.getX(), wetDrySlider.getBottom() + 5, wetDrySlider.getWidth(), 20);

    // Bottom Section
    auto bottomArea = bounds.removeFromBottom(220);

    // === Bottom Left: Low-Pass Filter ===
    auto filterArea = bottomArea.removeFromLeft(bottomArea.getWidth() / 2).reduced(10);
    lpflabel.setBounds(filterArea.removeFromTop(30).withSizeKeepingCentre(150, 20));
    cutoffSlider.setBounds(filterArea.withSizeKeepingCentre(150, 150).translated(0, -10)); // Slightly higher
    cutofflabel.setBounds(cutoffSlider.getX(), cutoffSlider.getBottom() + 5, cutoffSlider.getWidth(), 20);

    // === Bottom Right: Sample Playback ===
    auto sampleArea = bottomArea.reduced(10);
    samplelabel.setBounds(sampleArea.removeFromTop(30).withSizeKeepingCentre(150, 20));
    volumeslider.setBounds(sampleArea.withSizeKeepingCentre(150, 150).translated(0, -10)); // Slightly higher
    volumelabel.setBounds(volumeslider.getX(), volumeslider.getBottom() + 5, volumeslider.getWidth(), 20);

    // === Buttons Positioned in Between ===
    auto buttonArea = bottomArea.reduced(10);
    buttonArea.setWidth(200);
    buttonArea.setCentre(filterArea.getRight() + (sampleArea.getX() - filterArea.getRight()) / 2, bottomArea.getCentreY()); // Ensure vertical alignment

    sampleonButton.setBounds(buttonArea.removeFromTop(40).withSizeKeepingCentre(120, 25));
    rainButton.setBounds(buttonArea.removeFromTop(50).withSizeKeepingCentre(120, 25)); 
    vinylButton.setBounds(buttonArea.withSizeKeepingCentre(120, 25));
}


void PluginEditor::buttonClicked(juce::Button* button)
{
    if (button == &softclipButton)
    {
        processor.parameters.getParameterAsValue("saturationMode").setValue(0);
        softclipButton.setToggleState(true, juce::dontSendNotification);
        tapesaturationButton.setToggleState(false, juce::dontSendNotification);
        waveshapeButton.setToggleState(false, juce::dontSendNotification);
    }
    else if (button == &tapesaturationButton)
    {
        processor.parameters.getParameterAsValue("saturationMode").setValue(1);
        softclipButton.setToggleState(false, juce::dontSendNotification);
        tapesaturationButton.setToggleState(true, juce::dontSendNotification);
        waveshapeButton.setToggleState(false, juce::dontSendNotification);
    }
    else if (button == &waveshapeButton)
    {
        processor.parameters.getParameterAsValue("saturationMode").setValue(2);
        softclipButton.setToggleState(false, juce::dontSendNotification);
        tapesaturationButton.setToggleState(false, juce::dontSendNotification);
        waveshapeButton.setToggleState(true, juce::dontSendNotification);
    }

    if (button == &sampleonButton)
    {
        // Toggle playback state
        bool isPlaying = processor.parameters.getParameterAsValue("playState").getValue();
        processor.parameters.getParameterAsValue("playState").setValue(!isPlaying);

        // Enable/Disable Rain and Vinyl buttons based on playback state
        bool playbackEnabled = !isPlaying;
        rainButton.setEnabled(playbackEnabled);
        vinylButton.setEnabled(playbackEnabled);

        // Reset Rain and Vinyl button states if playback is stopped
        if (!playbackEnabled)
        {
            rainButton.setToggleState(false, juce::dontSendNotification);
            vinylButton.setToggleState(false, juce::dontSendNotification);
        }
    }
    // Handle Rain Button
    else if (button == &rainButton)
    {
        if (processor.parameters.getParameterAsValue("playState").getValue()) // Only if playback is active
        {
            processor.parameters.getParameterAsValue("sound").setValue(0); // Rain
            rainButton.setToggleState(true, juce::dontSendNotification);
            vinylButton.setToggleState(false, juce::dontSendNotification);
        }
    }
    // Handle Vinyl Button
    else if (button == &vinylButton)
    {
        if (processor.parameters.getParameterAsValue("playState").getValue()) // Only if playback is active
        {
            processor.parameters.getParameterAsValue("sound").setValue(1); // Vinyl
            rainButton.setToggleState(false, juce::dontSendNotification);
            vinylButton.setToggleState(true, juce::dontSendNotification);
        }
    }
}


  //SAMPLE PLAYBACK
    /*

    auto playbackButtonArea = centerArea.removeFromBottom(40);
    playButton.setBounds(playbackButtonArea.removeFromLeft(playbackButtonArea.getWidth() / 2).reduced(5));
    stopButton.setBounds(playbackButtonArea.reduced(5));

    */
    