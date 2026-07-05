/*
  ==============================================================================

	UIComponent.h
	Created: 4 Jul 2026 10:38:48am
	Author:  Dami

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AudioState.h"

class UIComponent : public juce::Component
{
public:
	UIComponent(AudioState& state) : audioState(state)
	{

		//DBG("asd");

	}
	~UIComponent()
	{

	}


	void paint(juce::Graphics& g) override
	{
		g.fillAll(juce::Colours::black);

		g.setColour(juce::Colours::red);

		for (auto& finger : audioState.fingers)
		{
			if (finger.active.load())
			{
				float x = finger.x.load();
				float y = finger.y.load();

				g.fillEllipse(x - 10.0f,
					y - 10.0f,
					20.0f,
					20.0f);
			}
		}
	}



	void mouseDown(const juce::MouseEvent& e) override
	{
		auto id = e.source.getIndex();

		if (id < audioState.fingers.size())
		{
			audioState.fingers[id].x.store(e.position.x);
			audioState.fingers[id].y.store(e.position.y);
			audioState.fingers[id].active.store(true);

			repaint();
		}
	}

	void mouseDrag(const juce::MouseEvent& e) override
	{
		auto id = e.source.getIndex();

		if (id < audioState.fingers.size())
		{
			audioState.fingers[id].x.store(e.position.x);
			audioState.fingers[id].y.store(e.position.y);

			repaint();
		}
	}

	void mouseUp(const juce::MouseEvent& e) override
	{
		auto id = e.source.getIndex();

		if (id < audioState.fingers.size())
		{
			audioState.fingers[id].active.store(false);

			repaint();
		}
	}



private:

	AudioState& audioState;

};


