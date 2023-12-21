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
NoiseGenerator::NoiseGenerator() {

    // Add level slider
    addAndMakeVisible(levelScaleSlider);
    levelScaleSlider.setRange(0, 1, 0.01);
    levelScaleSlider.setTextValueSuffix("");
    levelScaleSlider.addListener(this);
    //      ... and label
    addAndMakeVisible(levelScaleLabel);
    levelScaleLabel.setText("Level", juce::dontSendNotification);
    levelScaleLabel.attachToComponent(&levelScaleSlider, true);

    // Add offset slider
    addAndMakeVisible(levelOffsetSlider);
    levelOffsetSlider.setRange(-1, 1, 0.01);
    levelOffsetSlider.setTextValueSuffix("");
    levelOffsetSlider.addListener(this);
    //      ... and label
    addAndMakeVisible(levelOffsetLabel);
    levelOffsetLabel.setText("Offset", juce::dontSendNotification);
    levelOffsetLabel.attachToComponent(&levelOffsetSlider, true);
};
NoiseGenerator::~NoiseGenerator() { };

//==============================================================================
// Audio methods
//==============================================================================
/// <summary>
/// Add noise based on sliders to all channels of an audio buffer.
/// </summary>
void NoiseGenerator::addNoiseToBuffer(
    const juce::AudioSourceChannelInfo& bufferToFill)
{
    addNoiseToBuffer(bufferToFill, levelScale, levelOffset);
}

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

//==============================================================================
// Editor methods
//==============================================================================
void NoiseGenerator::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &levelScaleSlider) {
        levelScale = levelScaleSlider.getValue();
    }
    else if (slider == &levelOffsetSlider) {
        levelOffset = levelOffsetSlider.getValue();
    }
}

void NoiseGenerator::resized()
{
    // Note: outputs 0 0 0 0...
    //juce::Logger::getCurrentLogger()->writeToLog(getLocalBounds().toString());
    //setBounds(getLocalBounds());
 
    // TODO: align this with local bounds
    setSize(400, 100);
    
    auto sliderLeft = 40;
    levelScaleSlider.setBounds(sliderLeft, 20, getWidth() - sliderLeft, 20);
    levelOffsetSlider.setBounds(sliderLeft, 60, getWidth() - sliderLeft, 20);
}

void NoiseGenerator::paint(juce::Graphics& g) {
}