#pragma once

#include <JuceHeader.h>
#include "PluginEditor.h"

class PluginEditor;

class PluginProcessor : public juce::AudioProcessor
{
public:
    PluginProcessor();
    ~PluginProcessor() override;

    // Core AudioProcessor methods
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    AudioFormatManager formatManager;

    //Saturator modes
    enum class SaturationMode
    {
        softClip,
        tapeSaturation,
        waveShape
    };

    // Parameters
    juce::AudioProcessorValueTreeState parameters;

    friend class PluginEditor;

private:
    float inputGain = 0.0f;
    float outputGain = 0.0f; 

    // Saturation
    juce::dsp::WaveShaper<float> saturator;
    SaturationMode currentSaturationMode = SaturationMode::softClip;
    float threshold = 0.33f; 
    float drive = 5.0f; 

    // Filter - 2nd order - stage1, 1st order - stage2
    juce::OwnedArray<juce::dsp::IIR::Filter<float>> filters;
    juce::dsp::IIR::Filter<float> stage1; 
    juce::dsp::IIR::Filter<float> stage2; 

    // Helper methods
    void processSaturation(juce::AudioBuffer<float>& buffer);
    void processFilter(juce::AudioBuffer<float>& buffer);
    void processSamples(juce::AudioBuffer<float>& buffer);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};

