#pragma once
#pragma GCC diagnostic ignored "-Wunused-function"

#include <SDL2/SDL.h>
#include <cstdlib>
#include <math.h>

#include "Math.hpp"
#include "Line.hpp"


namespace Birb
{
	namespace utils
	{
		inline float hireTimeInSeconds()
		{
			float t = SDL_GetTicks();
			t *= 0.001f;

			return t;
		}

		void GetTextureDimensions(SDL_Texture* texture, int& x, int& y);
		SDL_Color TexturePixelToColor(Uint8* pixels, const Vector2int& pixelPosition, const int& textureWidth);
		std::vector<Vector2int> SortPath(const Vector2int& startPoint, const std::vector<Vector2int>& points);
		std::string CleanDecimals(const double& value); ///< Returns a string with without trailing zeroes in decimals

		Line* PolygonToLines(const Vector2f polygon[], const int& polygonSize);
	}
}
