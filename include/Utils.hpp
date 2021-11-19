#pragma once

//#include <SDL2/SDL.h>
//#include </usr/include/SDL2/SDL.h>
#include "../vendor/SDL2/SDL.h"
#include "../include/Math.hpp"
#include <iostream>
#include <cstdlib>
#include <math.h>


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

	Rect getInt()
	{
		Rect roundedRect;
		roundedRect.x = round(x);
		roundedRect.y = round(y);
		roundedRect.w = round(w);
		roundedRect.h = round(h);

		return roundedRect;
	}

	SDL_Rect getSDLRect()
	{
		SDL_Rect sdlrect;
		sdlrect.h = h;
		sdlrect.w = w;
		sdlrect.x = x;
		sdlrect.y = y;
		return sdlrect;
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

struct Texture
{
	SDL_Texture* sdlTexture;
	Vector2int dimensions;
};
