/*
  ==============================================================================

    NoiseGenerator.cpp
    Created: 9 Aug 2023 12:15:55am
    Author:  Kris Keillor

  ==============================================================================
*/

#include "NoiseGenerator.h"

//==============================================================================
// Constructor and Destructor
//==============================================================================
NoiseGenerator::NoiseGenerator() { };
NoiseGenerator::~NoiseGenerator() { };

//==============================================================================
// Audio methods
//==============================================================================
/// <summary>
/// Add noise with zero offset to all channels of an audio buffer.
/// </summary>
void NoiseGenerator::addNoiseToBuffer(
    const juce::AudioSourceChannelInfo& bufferToFill,
    float                               amplitude)
{
    float offset = amplitude / 2.0f;
    addNoiseToBuffer(bufferToFill, amplitude, offset);
}

/// <summary>
/// Add noise at a given offset to all channels of an audio buffer.
/// </summary>
void NoiseGenerator::addNoiseToBuffer(
    const juce::AudioSourceChannelInfo& bufferToFill, 
    float                               amplitude, 
    float                               offset)
{
    for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel) {
        /// Pointer to first sample index
        auto* buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

        // Generate noise
        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample) {
            buffer[sample] = random.nextFloat() * amplitude - offset;
        }
    }
}