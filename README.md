# LoloFX

LoloFX is an audio plugin that provides a set of audio processing tools, including a customizable saturator with multiple modes, a low-pass filter, and input/output gain controls. This plugin is designed to be a versatile tool for audio production, offering a smooth workflow and impactful sound design options.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)
- [License](#license)


## Features

### Saturator 
- Wet/Dry Mix:

    Blend processed and unprocessed signals for subtle or pronounced effects.

- Saturation Modes:

1.  Soft Clip: Gently limits the signal to avoid harsh clipping.

2.  Tape Saturation: Adds warm, analog-like saturation.

3. Wave Shaping: Uses an arctangent-based waveshaper for smooth distortion.
Low-Pass Filter:

### Low-Pass Filter
3rd-order Butterworth design for smooth high-frequency attenuation.

### Input/Output Gain:

Control levels entering and leaving the plugin to manage headroom and output loudness.

## System Requirements
Operating System:

Windows 10 or later / macOS 10.13 or later.

Software:

JUCE Framework (Version 6.1 or later).
Compatible DAW (e.g., Ableton Live, Logic Pro, FL Studio, etc.).
Hardware:

Minimum: Dual-Core Processor, 4 GB RAM.
Recommended: Quad-Core Processor, 8 GB RAM.

## Installation and Compilation

### Prerequisites
- Download and install the JUCE Framework.

- Ensure your development environment is set up:

- Windows: Visual Studio 2019 or later.

- macOS: Xcode 12 or later.

### Steps to Compile

1. Clone the Repository:

        git clone https://github.com/your-repo/lolofx.git
        cd lolofx

2. Open the Project:

- Locate the .jucer file in the project folder.

- Open it with the Projucer application.

3. Set Exporter:

Configure the project exporter for your target platform (e.g., Xcode, Visual Studio).

4. Build the Plugin:

    Open the project in the configured IDE.
    
    Compile and build the project to generate the VST3 or AU plugin file.

5. Install the Plugin:

    Copy the compiled .vst3 or .component file to your DAW's plugin directory:
    
    Windows: C:\Program Files\Common Files\VST3\
    
    macOS: /Library/Audio/Plug-Ins/Components/
    
## Configuration and Parameters

### Controls and Parameters
1. Saturation Section:

        a. Mode Buttons: Select between Soft Clip, Tape Saturation, and Wave Shaping modes.
        
        b. Threshold: Sets the threshold for soft clipping.

        c. Drive: Adjusts the intensity of saturation.
        
        d. Wet/Dry Mix: Balances the processed and unprocessed signals.

2. Filter Section:

        a. Cutoff Frequency: Adjusts the frequency at which the low-pass filter begins attenuating high frequencies.
        
3. Input/Output Gain:

        a. Input Gain: Controls the level of the audio signal entering the plugin.
        
        b. Output Gain: Controls the level of the audio signal leaving the plugin.

## Usage Instructions

### Adding LoloFX to Your DAW
1. Open your DAW and ensure it scans the plugin directory containing LoloFX.

2. Load LoloFX onto an audio track or an effects chain.

### Basic Workflow
1. Adjust the Input Gain slider to optimize the signal level.

2. Select a Saturation Mode and tweak the Threshold and Drive sliders for desired saturation.

3. Use the Wet/Dry Mix slider to blend the effect with the original signal.

4. Adjust the Cutoff Frequency to filter out unwanted high frequencies.

5. Set the Output Gain to ensure the final level is balanced.

## Troubleshooting
### The Plugin Is Not Showing in My DAW:

1. Verify the plugin file is in the correct directory.
2. Rescan plugins in your DAW.

### The Saturation Sounds Too Harsh:

1. Lower the Drive value.
2. Increase the Wet/Dry Mix to blend the effect.

### The Low-Pass Filter Is Not Working Properly:

1. Ensure the Cutoff Frequency is set above 20 Hz.
2. Check if your audio signal is routed through the plugin correctly.

### Contact Information
For any issues or questions, please contact:

Developer: Avanti Singh
Email: asingh3@berklee.edu

