/*
  ==============================================================================

	UIComponent.h
	Created: 4 Jul 2026 10:38:48am
	Author:  Dami

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class UIComponent : public juce::Component
{
public:
	UIComponent()
	{

		DBG("asd");

	}
	~UIComponent()
	{

	}


	void paint(juce::Graphics& g) override
	{
		g.fillAll(juce::Colours::black);

		g.setColour(juce::Colours::red);

		for (auto& finger : fingers)
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


	//std::map<int, juce::Point<float>> touches;

	void mouseDown(const juce::MouseEvent& e) override
	{
		auto id = e.source.getIndex();

		if (id < fingers.size())
		{
			fingers[id].x.store(e.position.x);
			fingers[id].y.store(e.position.y);
			fingers[id].active.store(true);

			repaint();
		}
	}

	void mouseDrag(const juce::MouseEvent& e) override
	{
		auto id = e.source.getIndex();

		if (id < fingers.size())
		{
			fingers[id].x.store(e.position.x);
			fingers[id].y.store(e.position.y);

			repaint();
		}
	}

	void mouseUp(const juce::MouseEvent& e) override
	{
		auto id = e.source.getIndex();

		if (id < fingers.size())
		{
			fingers[id].active.store(false);

			repaint();
		}
	}



private:

	juce::Point<int> myPoint;


	struct Finger
	{
		std::atomic<bool> active{ false };
		std::atomic<float> x{ 0.0f };
		std::atomic<float> y{ 0.0f };
	};

	std::array<Finger, 10> fingers;


	//std::array<Finger, 10> fingers;

};


