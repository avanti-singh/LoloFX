
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <algorithm>
#include <cmath>
#include <juce_dsp/juce_dsp.h>

//==============================================================================   

PluginProcessor::PluginProcessor()
    : AudioProcessor(BusesProperties()
                     .withInput("Input", juce::AudioChannelSet::stereo(), true)
                     .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      parameters(*this, nullptr, "PARAMETERS",
                 {
                     // Saturation parameters
                     std::make_unique<juce::AudioParameterChoice>("saturationMode", "Saturation Mode",
                         juce::StringArray{ "Soft Clip", "Tape Saturation", "Wave Shape" }, 0),
                     std::make_unique<juce::AudioParameterFloat>("threshold", "Threshold", -60.0f, 0.0f, -20.0f),
                     std::make_unique<juce::AudioParameterFloat>("drive", "Drive", 0.0f, 5.0f, 1.0f),
                     std::make_unique<juce::AudioParameterFloat>("wetDryMix", "Wet/Dry Mix",
                            juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f),

                     // Filter parameters
                     std::make_unique<juce::AudioParameterFloat>("cutoffFrequency", "Cutoff Frequency",
                         juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.5f), 1000.0f),

                    // Sample parameters
                    std::make_unique<juce::AudioParameterBool>("playState", "Play State", false),
                    std::make_unique<juce::AudioParameterFloat>("volume", "Volume", -60.0f, 0.0f, 1.0f),
                    std::make_unique<juce::AudioParameterChoice>("sound", "Sound", juce::StringArray{"Rain", "White Noise", "Crackle"}, 0),

                    // I/O GAIN - CHANGE THE RANGE
                    std::make_unique<juce::AudioParameterFloat>("inputGain", "Input Gain", -24.0f, 24.0f, 0.0f),
                    std::make_unique<juce::AudioParameterFloat>("outputGain", "Output Gain", -24.0f, 24.0f, 0.0f),
                 })

{
    formatManager.registerBasicFormats(); 
}

PluginProcessor::~PluginProcessor() = default;

const juce::String PluginProcessor::getName() const
{
    return "LoloFX";
}

bool PluginProcessor::hasEditor() const
{
    return true;
}

int PluginProcessor::getNumPrograms()
{
    return 1; 
}

int PluginProcessor::getCurrentProgram()
{
    return 0; 
}

void PluginProcessor::setCurrentProgram(int index)
{
    // Typically not used for single-program plugins
}

const juce::String PluginProcessor::getProgramName(int index)
{
    return {}; 
}

void PluginProcessor::changeProgramName(int index, const juce::String& newName)
{
    // Typically not used for single-program plugins
}

bool PluginProcessor::acceptsMidi() const
{
    return false; // Return true if the plugin processes MIDI input
}

bool PluginProcessor::producesMidi() const
{
    return false; // Return true if the plugin produces MIDI output
}

bool PluginProcessor::isMidiEffect() const
{
    return false; // Return true if the plugin is a pure MIDI effect
}

double PluginProcessor::getTailLengthSeconds() const
{
    return 0.0; // Return the tail length in seconds (0.0 for no tail)
}


void PluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    loadSamples(); 
    filters.clear();

    for (int i = 0; i < getTotalNumInputChannels(); ++i)
    {
        auto* filter = new juce::dsp::IIR::Filter<float>();
        auto coefficients = juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod(
            1000.0f, sampleRate, 3);
        
        if (!coefficients.isEmpty())
            filter->coefficients = coefficients.getUnchecked(0); 
        
        filters.add(std::move(filter));
    }
}


void PluginProcessor::releaseResources()
{

}

void PluginProcessor::loadSamples()
{
    // Load Rain Sample
    if (auto* reader = formatManager.createReaderFor(juce::File(sourcepathRain)))
    {
        rainbuff = std::make_unique<juce::AudioBuffer<float>>(reader->numChannels, (int)reader->lengthInSamples);
        reader->read(rainbuff.get(), 0, (int)reader->lengthInSamples, 0, true, true);
    }

    // Load Vinyl Sample
    if (auto* reader = formatManager.createReaderFor(juce::File(sourcepathVinyl)))
    {
        vinylbuff = std::make_unique<juce::AudioBuffer<float>>(reader->numChannels, (int)reader->lengthInSamples);
        reader->read(vinylbuff.get(), 0, (int)reader->lengthInSamples, 0, true, true);
    }
}


// Define the sign function
template <typename T>
int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

void PluginProcessor::processSaturation(juce::AudioBuffer<float>& buffer)
{
    float currentThreshold = parameters.getRawParameterValue("threshold")->load();
    float currentDrive = parameters.getRawParameterValue("drive")->load() * 0.5f; 

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();

    const float outputScaling = 0.7f; 

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int data = 0; data < buffer.getNumSamples(); ++data)
        {
            float inputSample = channelData[data];
            float x = channelData[data] * currentDrive;
            float processed = x;

            switch (currentSaturationMode)
            {
                case SaturationMode::softClip:
                    if (x > 1.0f) 
                        x = 1.0f;
                    else if (x < -1.0f)
                        x = -1.0f;
                    processed = 1.5f * x - 0.5f * x * x * x;
                    break;

                case SaturationMode::tapeSaturation:
                    processed = std::tanh(x * 0.6f);
                    processed = 0.9f * processed + 0.1f * inputSample; 
                    break;

                case SaturationMode::waveShape:
                    processed = std::atan(processed * 1.2f); 
                    processed = 0.8f * processed + 0.2f * inputSample; 
                    break;

                default:
                    jassertfalse;
                    break;
            }

            // Apply output scaling
            channelData[data] = processed * outputScaling;
        }
    }
}

void PluginProcessor::processFilter(juce::AudioBuffer<float>& buffer)
{
    float currentCutoff = parameters.getRawParameterValue("cutoffFrequency")->load();

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        // Generate coefficients for Butterworth filter
        auto coefficients = juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod(
            currentCutoff, getSampleRate(), 6); 

        if (!coefficients.isEmpty())
            filters[channel]->coefficients = coefficients.getUnchecked(0);

        // Create an AudioBlock for the channel
        juce::dsp::AudioBlock<float> block(buffer);
        auto channelBlock = block.getSingleChannelBlock(channel);
        juce::dsp::ProcessContextReplacing<float> context(channelBlock);

        // Process the channel through the filter
        filters[channel]->process(context);
    }
}

void PluginProcessor::processSamples(juce::AudioBuffer<float>& buffer)
{
    auto playState = parameters.getRawParameterValue("playState")->load();
    auto volume = parameters.getRawParameterValue("volume")->load();
    auto soundSelection = parameters.getRawParameterValue("sound")->load();

    if (!playState || volume <= 0.0f) // Check if playback is off
        return;

    // Select the correct buffer
    auto* selectedBuffer = (soundSelection == 0) ? rainbuff.get()
                         : (soundSelection == 1) ? vinylbuff.get()
                         : nullptr;

    if (selectedBuffer == nullptr)
        return;

    int totalSamples = buffer.getNumSamples();

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* output = buffer.getWritePointer(channel);
        auto* input = selectedBuffer->getReadPointer(channel % selectedBuffer->getNumChannels());

        for (int sample = 0; sample < totalSamples; ++sample)
        {
            // Wrap playback position
            output[sample] += input[playbackPosition % selectedBuffer->getNumSamples()] * volume;
            ++playbackPosition;
        }
    }
}



void PluginProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    currentSaturationMode = static_cast<SaturationMode>(
        parameters.getRawParameterValue("saturationMode")->load());

    float inputGain = juce::Decibels::decibelsToGain(parameters.getRawParameterValue("inputGain")->load());
    buffer.applyGain(inputGain);

    processSaturation(buffer); 
    processFilter(buffer);   
    processSamples(buffer);  

    float outputGain = juce::Decibels::decibelsToGain(parameters.getRawParameterValue("outputGain")->load());
    buffer.applyGain(outputGain); 
}

void PluginProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PluginProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml && xml->hasTagName(parameters.state.getType()))
        parameters.replaceState(juce::ValueTree::fromXml(*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}

juce::AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor(*this);
}
