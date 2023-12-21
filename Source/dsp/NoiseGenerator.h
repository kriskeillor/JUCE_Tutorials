/*
  ==============================================================================

    NoiseGenerator.h
    Created: 9 Aug 2023 12:15:55am
    Author:  Kris Keillor

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class NoiseGenerator :  public juce::Component,
                        public juce::Slider::Listener {
public:
    //==============================================================================
    // Types
    //==============================================================================
    enum Mode {
        ///  Overwrite and clamp between -1 and 1.
        Write = 0,
        ///  Add and clamp between -1 and 1.
        Add = 1,
        ///  Overwrite allowing saturation beyond +/-1.
        WriteSat = 2,
        ///  Add allowing saturation beyond +/-1.
        AddSat = 3,
    };

    //==============================================================================
    // Constructor and Destructor
    //==============================================================================
    NoiseGenerator();
    ~NoiseGenerator();

    //==============================================================================
    // Audio methods
    //==============================================================================
    void addNoiseToBuffer(const juce::AudioSourceChannelInfo& bufferToFill);
    void addNoiseToBuffer(const juce::AudioSourceChannelInfo& bufferToFill, float amplitude);
    void addNoiseToBuffer(const juce::AudioSourceChannelInfo& bufferToFill, float amplitude, float offset);

    //==============================================================================
    // Editor methods
    //==============================================================================
    void sliderValueChanged(juce::Slider* slider) override;    // Mandatory override
    void resized() override;                                   // Mandatory override
    void paint(juce::Graphics&) override;                      // Mandatory override

private:
    // Parameters
    float levelScale { 0.0f }, 
          levelOffset{ 0.0f };

    // Editor Components
    juce::Slider levelScaleSlider, levelOffsetSlider;
    juce::Label  levelScaleLabel,  levelOffsetLabel;

    // Utility
    juce::Random random;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NoiseGenerator)
};