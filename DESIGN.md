# Design Document: LoloFX

## Overview
LoloFX is a real-time audio effects plugin designed for creating unique and customizable lo-fi sounds. This project implements a saturator with three modes (Soft Clip, Tape Saturation, and Wave Shaping) and a third-order Butterworth low-pass filter. The plugin provides real-time control over parameters such as threshold, drive, cutoff frequency, and wet/dry mix, making it ideal for creative sound design.

The design process focused on balancing ease of use, performance, and sonic versatility. Below, we discuss the key technical components and design decisions made during the development of this project.

---

## Features

### 1. Saturator
- **Modes**: Soft Clip, Tape Saturation, Wave Shaping.
- **Parameters**:
  - `Threshold`: Controls the level above which soft clipping or saturation occurs.
  - `Drive`: Amplifies the input signal before applying saturation.
  - `Wet/Dry Mix`: Balances between processed and unprocessed signals.
- **Implementation**: Each mode uses distinct mathematical models:
  - **Soft Clip**: Cubic waveshaper.
  - **Tape Saturation**: Uses `std::tanh` for analog-like characteristics.
  - **Wave Shaping**: Relies on an arctangent function for a softer response.

### 2. Low-Pass Filter
- **Type**: Third-order Butterworth filter for smooth frequency roll-off.
- **Parameter**: 
  - `Cutoff Frequency`: Determines the filter's cutoff point (20 Hz - 20 kHz).
- **Implementation**: Coefficients are dynamically designed using JUCE's DSP library.

### 3. Real-Time Parameter Control
- Utilizes JUCE's `AudioProcessorValueTreeState` for efficient and thread-safe parameter management.

### 4. UI Design
- Custom rotary sliders and toggle buttons provide intuitive control.
- Labels and a consistent color scheme enhance usability.

---

## Implementation Details

### 1. Saturation Modes
Each saturation mode processes the audio buffer differently:

#### **Soft Clip**
- **Formula**: `y = 1.5x - 0.5x^3` for values between `-1` and `1`, with clipping outside this range.
- **Output Shaping**: Ensures a smooth transition near the threshold.
- **Decision**: This mode was chosen for its balance between natural warmth and clarity, making it ideal for lo-fi aesthetics.

#### **Tape Saturation**
- **Formula**: `y = std::tanh(x * 0.6)` with an additional blend of the input signal.
- **Decision**: Tape saturation mimics analog tape characteristics, adding harmonic richness without excessive distortion.

#### **Wave Shaping**
- **Formula**: `y = atan(x)`.
- **Decision**: Arctangent shaping provides a softer distortion curve, suitable for subtle harmonic enhancement.

### 2. Low-Pass Filter
- **Filter Design**: 
  - Third-order Butterworth filter ensures smooth roll-off with minimal phase distortion.
  - Dynamic coefficient generation adjusts the filter in real time based on the cutoff frequency.
- **Block-Based Processing**:
  - Audio is processed in blocks to optimize performance while avoiding audible artifacts.
- **Decision**: Block-based processing ensures low latency and compatibility with real-time audio environments.

### 3. Parameter Management
- **JUCE's AudioProcessorValueTreeState**:
  - All parameters (e.g., threshold, drive, cutoff) are managed centrally.
  - **Decision**: Ensures thread safety and seamless UI-to-audio synchronization.

### 4. User Interface
- **Custom LookAndFeel**:
  - Custom rotary sliders and buttons align with the lo-fi aesthetic.
  - **Decision**: Unique visual design enhances user experience and distinguishes LoloFX.

---

## Design Decisions

### Balancing Performance and Quality
- Block-based processing minimizes CPU usage while maintaining high audio quality.
- Each saturator mode offers distinct sonic character, balancing versatility and usability.

### Avoiding Overly Harsh Sound
- Saturation output scaling and blending with the input signal ensure usable tones without excessive harshness.

### Extensibility
- The codebase is structured to allow easy addition of new effects or UI elements (e.g., new filter types or saturation modes).

---

## Challenges and Solutions

### Challenge: Filter Resonance and Noise
- **Issue**: The low-pass filter initially exhibited high resonance and noise.
- **Solution**: Clamping the cutoff frequency and fine-tuning the Butterworth design parameters reduced artifacts.

### Challenge: Overly Harsh Saturation
- **Issue**: Early saturation implementations were too aggressive.
- **Solution**: Output scaling and harmonic blending softened the sound while preserving character.

### Challenge: Real-Time Parameter Updates
- **Issue**: Ensuring smooth transitions during parameter changes.
- **Solution**: Leveraging JUCE's `AudioProcessorValueTreeState` eliminated glitches during real-time control adjustments.

---

## Future Improvements
- Add additional filter types (e.g., high-pass, band-pass).
- Expand saturation modes for more aggressive distortion options.
- Include a visualizer for the filter's frequency response.
- Enhance UI animations for a more dynamic experience.

---

## Conclusion
LoloFX is a carefully designed lo-fi audio plugin that combines smooth filtering and versatile saturation. The technical choices behind its development prioritize quality, usability, and extensibility. This design document serves as a blueprint for understanding the plugin's implementation and the rationale behind its features.
