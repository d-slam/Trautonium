#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	addAndMakeVisible(keyboard);

	formatManager.addFormat(std::make_unique<juce::VST3PluginFormat>());
	formatManager.addFormat(std::make_unique<juce::VSTPluginFormat>());

	loadPlugin();

	setSize(800, 400);
	setAudioChannels(0, 2);
}

MainComponent::~MainComponent()
{
	shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	if (plugin) plugin->prepareToPlay(sampleRate, samplesPerBlockExpected);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	auto& buffer = *bufferToFill.buffer;

	buffer.clear();

	juce::MidiBuffer midi;

	keyboardState.processNextMidiBuffer(midi, bufferToFill.startSample, bufferToFill.numSamples, true);

	if (plugin) plugin->processBlock(buffer, midi);
}

void MainComponent::releaseResources()
{

}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
	auto area = getLocalBounds();

	auto pluginArea = area.removeFromTop(getHeight() / 2);
	auto keyboardArea = area;

	if (pluginEditor) pluginEditor->setBounds(pluginArea);

	keyboard.setBounds(keyboardArea);
}


void MainComponent::loadPlugin()
{
	juce::PluginDescription desc;

	desc.fileOrIdentifier =
		"C:\\JUCE\\damiProjects26\\VSTHost\\Source\\Quilcom-Trout_Win64\\Quilcom Trout v1.018 (64).dll";

	desc.pluginFormatName = "VST";
	desc.uniqueId = 0;

	juce::String error;

	plugin = formatManager.createPluginInstance(desc, 44100.0, 512, error);

	if (!plugin)
	{
		DBG("Plugin load failed: " + error);
		return;
	}

	DBG("Plugin loaded!");

	pluginEditor.reset(plugin->createEditorIfNeeded());

	if (pluginEditor)
	{
		addAndMakeVisible(pluginEditor.get());
		pluginEditor->toFront(true);
		resized();
	}
}