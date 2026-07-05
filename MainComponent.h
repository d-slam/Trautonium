#pragma once

#include <JuceHeader.h>

class MainComponent : public juce::AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected,
        double sampleRate) override;

    void getNextAudioBlock(const juce::AudioSourceChannelInfo&) override;
    void releaseResources() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void loadPlugin();

    juce::AudioPluginFormatManager formatManager;
    std::unique_ptr<juce::AudioPluginInstance> plugin;

    std::unique_ptr<juce::AudioProcessorEditor> pluginEditor;

    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboard
    {
        keyboardState,
        juce::MidiKeyboardComponent::horizontalKeyboard
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};