# Minimum required version of CMake.
cmake_minimum_required(VERSION 3.15)

# Set the executable name as a variable, which we will use elsewhere in this
# CMakeLists.txt file so we don't have to type it multiple times.
set(EXEC_NAME LoloFX)

# Set the project name and version.
project(${EXEC_NAME} VERSION 1.0.0)

# Set the C++ standard to use.
set(CMAKE_CXX_STANDARD 17)

# Path to the JUCE library.
add_subdirectory("../JUCE" "${CMAKE_BINARY_DIR}/JUCE")

# Create a JUCE plugin
juce_add_plugin(${EXEC_NAME}
    FORMATS AU VST3 Standalone
    COMPANY_NAME "EP-353"
    PLUGIN_NAME "LoloFX" # Updated plugin name
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
)

# List your source files
target_sources(${EXEC_NAME}
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginProcessor.h
        Source/PluginEditor.cpp
        Source/PluginEditor.h
)

# Link JUCE modules
target_link_libraries(${EXEC_NAME}
    PRIVATE
        juce::juce_core
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_plugin_client
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_data_structures
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
        juce::juce_dsp
)

target_compile_definitions(${EXEC_NAME}
    PRIVATE
        JUCE_PLUGINHOST_VST=0
        JUCE_VST2_SDK_ENABLED=0
)

# Generate JuceHeader.h for simplified includes
juce_generate_juce_header(${EXEC_NAME})
