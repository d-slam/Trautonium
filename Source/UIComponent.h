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
		g.drawEllipse(myPoint.getX(), myPoint.getY(), 5, 5, 5.0f);

	}


	void mouseDown(const juce::MouseEvent& event) override
	{
		auto pos = event.getPosition();
		myPoint = event.getPosition();

		DBG("x = " << pos.x);
		DBG("y = " << pos.y);

		repaint();

	}

	void mouseDrag(const juce::MouseEvent& event) override
	{
		auto pos = event.getPosition();
		myPoint = event.getPosition();


		DBG(pos.x << ", " << pos.y);

		repaint();
	}

private:

	juce::Point<int> myPoint;

};