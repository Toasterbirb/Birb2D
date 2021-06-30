#pragma once

//#include <SDL2/SDL.h>
#include </usr/include/SDL2/SDL.h>
#include <iostream>
#include <cstdlib>

namespace utils
{
	inline float hireTimeInSeconds()
	{
		float t = SDL_GetTicks();
		t *= 0.001f;

		return t;
	}

	inline int randomInt(int min, int max)
	{
		srand(time(0));
		float value = rand() % (max + 1 - min) + min;
		return value;
	}

	inline float randomFloat(float min, float max)
	{
		srand(time(0));
		float random = ((float) rand()) / (float) RAND_MAX;
		float range = max - min;
		return (random * range) + min;
	}
}
