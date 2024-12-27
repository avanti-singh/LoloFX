#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class PluginProcessor;

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:

    void setKnobImage(const juce::Image& image)
        {
            knobImage = image;
        }

     void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPos, float minSliderPos, float maxSliderPos,
                          const juce::Slider::SliderStyle, juce::Slider& slider) override
    {
        // Draw the background of the slider
        g.fillAll(slider.findColour(juce::Slider::backgroundColourId));

        // Draw the border of the slider
        g.setColour(juce::Colours::white);
        g.drawRect(x, y, width, height, 2);

        // Draw the slider thumb
        g.setColour(slider.findColour(juce::Slider::thumbColourId));
        g.fillRect(static_cast<float>(x), sliderPos - 5.0f, static_cast<float>(width), 10.0f);
    }

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
    {
        auto radius = jmin(width / 2, height / 2) - 4.0f;
        auto centerX = x + width * 0.5f;
        auto centerY = y + height * 0.5f;
        
        if (!knobImage.isNull())
        {
            g.drawImageWithin(knobImage, x, y, width, height, juce::RectanglePlacement::centred);
        }
        else
        {
            // Fallback if the image is missing
            g.setColour(juce::Colours::grey);
            g.fillEllipse(x, y, width, height);
        }

        auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

        auto thumbRadius = radius * 0.50f;
        auto thumbX = centerX + thumbRadius * std::cos(angle - MathConstants<float>::pi / 2.0f);
        auto thumbY = centerY + thumbRadius * std::sin(angle - MathConstants<float>::pi / 2.0f);
        auto thumbWidth = 6.0f;

        g.setColour(Colour(0xFF00FFFF));
        g.fillEllipse(thumbX - thumbWidth * 0.5f, thumbY - thumbWidth * 0.5f,
                  thumbWidth, thumbWidth);

        float arcThickness = 3.0f; 
        g.setColour(juce::Colours::cyan);
        juce::Path arcPath;
        arcPath.addCentredArc(centerX, centerY, radius + 2.0f, radius + 2.0f, 0.0f, rotaryStartAngle, angle, true);
        g.strokePath(arcPath, PathStrokeType(arcThickness));    
    }

    void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                                             bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        auto bounds = button.getLocalBounds().toFloat();
        juce::Colour baseColour = backgroundColour;

        if (button.getToggleState()) 
            baseColour = juce::Colours::blue;
        else if (shouldDrawButtonAsHighlighted) 
            baseColour = baseColour.brighter(0.2f);
        else if (shouldDrawButtonAsDown) 
            baseColour = baseColour.darker(0.2f);

        // Draw button background
        g.setColour(baseColour);
        g.fillRoundedRectangle(bounds, 6.0f);

        // Draw outline
        g.setColour(juce::Colours::white);
        g.drawRoundedRectangle(bounds, 6.0f, 2.0f);
    }

    void drawButtonText(Graphics& g, TextButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        auto font = Font(16.0f, Font::bold);
        g.setFont(font);

        // Button text color
        g.setColour(Colour(0xFFFFECEF));

        auto bounds = button.getLocalBounds();
        g.drawFittedText(button.getButtonText(), bounds, Justification::centred, 1);
    }

    private:
    juce::File knobFile;
    juce::Image knobImage;
};

class PluginEditor : public juce::AudioProcessorEditor, public juce::Button::Listener
{
public:
    explicit PluginEditor(PluginProcessor& processor);
    ~PluginEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;

private:
    PluginProcessor& processor;

    juce::Image backgroundImage;

    juce::File knobFile;
    juce::Image knobImage;

    std::unique_ptr<CustomLookAndFeel> customLookAndFeel = std::make_unique<CustomLookAndFeel>();
    
    juce::Label pluginname;

    juce::Slider inputGainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputGainAttachment;

    juce::Slider outputGainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputGainAttachment;

    //Saturator Mode Buttons:
    TextButton softclipButton; 
    TextButton tapesaturationButton; 
    TextButton waveshapeButton; 

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> softclipAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> tapesaturationAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> waveshapeAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> sampleonAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> rainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> vinylAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volumeAttachment;

    // Saturator UI Components
    juce::Label saturatorlabel;

    juce::Label thresholdlabel;
    juce::Slider thresholdSlider;

    juce::Label drivelabel;
    juce::Slider driveSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> saturationTHAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> saturationDRAttachment;

    juce::Label wetdrylabel;
    juce::Slider wetDrySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetDryAttachment;

    // Filter UI Components
    juce::Label lpflabel;

    juce::Label cutofflabel;
    juce::Slider cutoffSlider;

    //Sample UI Components
    TextButton sampleonButton;
    juce::Label samplelabel;

    TextButton rainButton;
    TextButton vinylButton;

    juce::Label volumelabel;
    juce::Slider volumeslider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
