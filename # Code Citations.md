# Code Citations

## License: unknown
https://github.com/Bej9038/EQ/tree/9b3c717913fcbbe323c54d2148c17606aadde7d3/EQ/Source/PluginProcessor.h

```
void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const
```


## License: unknown
https://github.com/DISTRHO/DISTRHO-Ports/tree/a38bb0d4738f88279f896e2c058e3df1ad570578/ports-juce6.1/swankyamp/source/PluginProcessor.h

```
getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const
```


## License: unknown
https://github.com/stekyne/PhaseVocoder/tree/8adcd181dd88c69d3ba906f0282c47b7ad735fd5/PluginProcessor.h

```
() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override
```


## License: GPL_3_0
https://github.com/werman/noise-suppression-for-voice/tree/c1cf4307c75abed8e3ecccdd23a35f7782feaf69/src/juce_plugin/RnNoiseAudioProcessor.h

```
;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override
```


## License: GPL_3_0
https://github.com/rclement/meeblip-controller/tree/382ad2ea64a04184e9887451b8aa9fcdeb42aacb/src/plugin/PluginProcessor.h

```
&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect(
```

