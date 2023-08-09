#include "MainComponent.h"

//==============================================================================
// Constructor and Destructor
//==============================================================================
MainComponent::MainComponent()
{
    // Add child components
    // ...addChild()...

    // Set component size 
    setSize (400, 600);

    // Request permissions to open input channels 
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Mandatory call to specify the number of input/output channels
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // Mandatory call to shut down the audio device and clear the audio source
    shutdownAudio();
}

//==============================================================================
// Audio Methods
//==============================================================================
/// <summary>
/// Called from audio thread when audio device is started or its settings changed.
/// </summary>
/// <param name="samplesPerBlockExpected">: Size, in samples, of the audio buffers 
///     requested from getNextAudioBlock()</param>
/// <param name="sampleRate">: Current sample rate of the hardware</param>
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    juce::String msg;
    msg << "Preparing to play audio.\n";
    msg << "samplesPerBlockExpected: \n" << samplesPerBlockExpected << "\n";
    msg << "sampleRate: \n" << sampleRate << "\n";
    juce::Logger::getCurrentLogger()->writeToLog(msg);
}

/// <summary>
///  Called by audio thread and returns audio blocks.
/// </summary>
/// <param name="bufferToFill">: Multichannel audio buffer 
///     { AudioSampleBuffer* buffer, int startSample, int numSamples }.</param>
void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    noiseGen.addNoiseToBuffer(bufferToFill, 0.25f);
}

/// <summary>
/// Called when the audio device stops or is restarted
/// </summary>
void MainComponent::releaseResources()
{
    juce::Logger::getCurrentLogger()->writeToLog("Releasing audio resources");
}

//==============================================================================
// Editor Methods
//==============================================================================
/// <summary>
/// Draw component (and child components?)
/// </summary>
/// <param name="g">: Graphics context</param>
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

/// <summary>
/// Called when the MainContentComponent is resized to recompose editor
/// </summary>
void MainComponent::resized()
{
}
