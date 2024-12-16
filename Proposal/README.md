# Proposal

## What will (likely) be the title of your project?

Lolo FX

## In just a sentence or two, summarize your project. (E.g., "My project is about creating a wavetable synthesizer.")

My project is to create a lo-fi audio effect plugin with a saturator, low-pass filter, reverb, and noise/crackle/rain generator. This plugin aims to help musicians and producers achieve a nostalgic, warm, and vintage sound.

## In a paragraph or more, detail your project. What will your software do? What features will it have? How will it be executed?

My audio effect software, Lolo FX, will simulate the imperfections and warmth of retro audio devices, such as cassette tapes and vinyl records. The plugin will include four main features:

1. Saturator to emulate analog-style distortion and warmth.

2. Low-Pass Filter (LPF) to create a muffled, vintage effect by removing high frequencies.

3. Noise/Crackle/Rain Generator to introduce vinyl crackle, tape hiss, or rainy ambience.

4. Reverb to add depth and space with a lo-fi aesthetic (e.g., small-room or spring reverb).

Lolo FX will be built using JUCE, with modular DSP components for each effect. The user interface will be minimal yet aesthetically pleasing, offering intuitive controls for the parameters. The plugin will work as a VST/AU and be tested for compatibility with popular DAWs.

## If you are planning to combine EP-353's final project with another course's project, which other course? And which aspect(s) of your proposed project would relate to EP-353, and which aspect(s) would connect to the other course?
N/A


### In the software world, almost everything takes longer to implement than you expect. And it is not uncommon to accomplish less in a fixed amount of time than you hope.

## In a sentence (or list of features), define a GOOD outcome for your final project. I.e., what WILL you accomplish no matter what?
A working plugin with basic functionality: saturation, low-pass filter, and noise generator integrated into the signal chain.
Functional UI controls for all implemented features.

## In a sentence (or list of features), define a BETTER outcome for your final project. I.e., what do you THINK you can accomplish before the final project's deadline?
All features implemented, including saturation, low-pass filter, noise generator, and reverb.
A cohesive, well-designed user interface with labeled controls and responsive interaction.
Tested and optimized for real-time use in DAWs.

## In a sentence (or list of features), define a BEST outcome for your final project. I.e., what do you HOPE to accomplish before the final project's deadline?
- Fully polished plugin with a visually engaging, retro-inspired user interface.
- Multiple noise types (e.g., vinyl crackle, tape hiss, rain) selectable via the UI.
- A preset system with predefined lo-fi styles like "Old Radio" or "Tape Deck."
- Automation-ready parameters for use in DAWs.
Additional features like wow and flutter effects or stereo imaging options.

## In a paragraph or more, outline your next steps. What new skills will you need to acquire? What topics will you need to research?
The first step is to set up the JUCE project and design a basic UI layout with placeholders for each control. Next, I will focus on implementing the DSP components for each effect, starting with the saturator. I will need to research DSP algorithms for saturation, filtering, and reverb, as well as techniques for generating and blending noise textures. Additionally, I’ll explore how to integrate modular DSP components into a single signal chain. On the UI side, I’ll learn how to create custom graphics and responsive controls using JUCE's GUI tools. Finally, I will test and debug the plugin in different DAWs to ensure smooth performance and compatibility.

