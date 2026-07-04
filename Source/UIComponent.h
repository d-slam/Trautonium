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
		// Hintergrund
		g.fillAll(juce::Colours::darkgrey);

		// Rand
		g.setColour(juce::Colours::white);
		g.drawRect(getLocalBounds(), 2);

		g.setColour(juce::Colours::red);
		//g.drawEllipse(myPoint.getX(), myPoint.getY(), 5, 5, 5.0f);


		 // Alle aktiven Finger zeichnen
		g.setColour(juce::Colours::red);

		for (const auto& touch : touches)
		{
			auto pos = touch.second;

			float radius = 10.0f;

			g.fillEllipse(pos.x - radius,
				pos.y - radius,
				radius * 2.0f,
				radius * 2.0f);
		}

	}


	std::map<int, juce::Point<float>> touches;

	void mouseDown(const juce::MouseEvent& e) override
	{
		touches[e.source.getIndex()] = e.position;
		repaint();
	}

	void mouseDrag(const juce::MouseEvent& e) override
	{
		touches[e.source.getIndex()] = e.position;
		repaint();
	}

	void mouseUp(const juce::MouseEvent& e) override
	{
		touches.erase(e.source.getIndex());
		repaint();
	}



private:

	juce::Point<int> myPoint;

};