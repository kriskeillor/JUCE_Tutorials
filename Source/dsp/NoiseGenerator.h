/*
  ==============================================================================

    NoiseGenerator.h
    Created: 9 Aug 2023 12:15:55am
    Author:  Kris Keillor

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class NoiseGenerator {
public:
    //==============================================================================
    // Types
    //==============================================================================
    enum Mode {
        Write = 0,
        Add = 1
    };

    //==============================================================================
    // Constructor and Destructor
    //==============================================================================
    NoiseGenerator();
    ~NoiseGenerator();

    //==============================================================================
    // Audio methods
    //==============================================================================
    void addNoiseToBuffer(const juce::AudioSourceChannelInfo& bufferToFill, float amplitude);
    void addNoiseToBuffer(const juce::AudioSourceChannelInfo& bufferToFill, float amplitude, float offset);

private:
    juce::Random random;
};