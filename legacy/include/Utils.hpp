#pragma once

#include <SDL2/SDL.h>

#include "../include/Math.hpp"
#include <iostream>
#include <cstdlib>
#include <math.h>


struct Rect
{
	Rect();
	Rect(float p_x, float p_y, float p_w, float p_h);

	void print()
	{
		std::cout << x << ", " << y << ", " << w << ", " << h << std::endl;
	}

	Rect getInt();

	SDL_Rect getSDLRect();

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

namespace Birb2D
{
	struct Texture
	{
		Texture();
		Texture(SDL_Texture* p_sdlTexture, Vector2int p_dimensions);
		SDL_Texture* sdlTexture;
		Vector2int dimensions;
	};
}
