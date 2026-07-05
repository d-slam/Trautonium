/*
  ==============================================================================

    AudioState.h
    Created: 5 Jul 2026 10:33:30am
    Author:  Dami

  ==============================================================================
*/

#pragma once


#include <atomic>

struct AudioState
{

	struct Finger
	{
		std::atomic<bool> active{ false };
		std::atomic<float> x{ 0.0f };
		std::atomic<float> y{ 0.0f };
	};

	std::array<Finger, 10> fingers;
		

};