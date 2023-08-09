#pragma once

#include <JuceHeader.h>
#include "dsp/NoiseGenerator.h"

/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    // Constructor and Destructor
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    // Audio methods
    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    // Editor methods
    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    NoiseGenerator noiseGen;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
