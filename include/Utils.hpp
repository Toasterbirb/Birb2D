#pragma once

//#include <SDL2/SDL.h>
//#include </usr/include/SDL2/SDL.h>
#include "../vendor/SDL2/SDL.h"
#include <iostream>
#include <cstdlib>

struct Rect
{
	Rect()
	:x(0.0f), y(0.0f), w(0.0f), h(0.0f)
	{}

	Rect(float p_x, float p_y, float p_w, float p_h)
	:x(p_x), y(p_y), w(p_w), h(p_h)
	{}

	void print()
	{
		std::cout << x << ", " << y << ", " << w << ", " << h << std::endl;
	}

	float x, y, w, h;
};

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
