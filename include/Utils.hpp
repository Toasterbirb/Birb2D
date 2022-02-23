#pragma once
#pragma GCC diagnostic ignored "-Wunused-function"

#include <SDL2/SDL.h>

#include "Math.hpp"
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <random>


namespace Birb
{
	struct Rect
	{
		Rect();
		Rect(const float& p_x, const float& p_y, const float& p_w, const float& p_h);

		void print()
		{
			std::cout << x << ", " << y << ", " << w << ", " << h << std::endl;
		}

		std::string toString()
		{
			return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(w) + ", " + std::to_string(h);
		}

		Rect getInt();
		SDL_Rect getSDLRect() const;

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

		static bool RandomGenInitialized = false;
		inline void InitRandomGen()
		{
			srand(time(0));
			RandomGenInitialized = true;
		}

		inline int randomInt(const int& min, const int& max)
		{
			if (!RandomGenInitialized)
				InitRandomGen();

			float value = rand() % (max + 1 - min) + min;
			return value;
			
			//std::cout << time(0) << std::endl;
			//std::minstd_rand generator(time(0));
			//std::uniform_int_distribution<int> distribution(min, max);
			//return distribution(generator);
		}

		inline float randomFloat(const float& min, const float& max)
		{
			if (!RandomGenInitialized)
				InitRandomGen();

			float random = ((float) rand()) / (float) RAND_MAX;
			float range = max - min;
			return (random * range) + min;
		}

		static void GetTextureDimensions(SDL_Texture* texture, int& x, int& y)
		{
			SDL_QueryTexture(texture, NULL, NULL, &x, &y);
		}

		static SDL_Color TexturePixelToColor(Uint8* pixels, const Vector2int& pixelPosition, const int& textureWidth)
		{
			// Some weird BGRA format
			Uint8 b = pixels[4 * (pixelPosition.y * textureWidth + pixelPosition.x) + 0]; // Blue
			Uint8 g = pixels[4 * (pixelPosition.y * textureWidth + pixelPosition.x) + 1]; // Green
			Uint8 r = pixels[4 * (pixelPosition.y * textureWidth + pixelPosition.x) + 2]; // Red
			Uint8 a = pixels[4 * (pixelPosition.y * textureWidth + pixelPosition.x) + 3]; // Alpha
			
			SDL_Color color = { r, g, b, a };
			
			return color;
		}

		std::vector<Vector2int> SortPath(const Vector2int& startPoint, const std::vector<Vector2int>& points);
	}
}

//namespace Birb2D
//{
//	/// Deprecated way of handling textures. Kept for now, but please don't use this
//	struct Texture
//	{
//		Texture();
//		Texture(SDL_Texture* p_sdlTexture, Vector2int p_dimensions);
//		SDL_Texture* sdlTexture;
//		Vector2int dimensions;
//	};
//
//}
