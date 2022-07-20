#pragma once
#pragma GCC diagnostic ignored "-Wunused-function"

#include "SDL.hpp"
#include <Logger.hpp>

#include <cstdlib>
#include <math.h>

#include "Math.hpp"
#include "Line.hpp"


namespace Birb
{
	namespace utils
	{
#ifdef LIB_SDL
		inline float hireTimeInSeconds()
		{
			float t = SDL_GetTicks();
			t *= 0.001f;

			return t;
		}

		Vector2int GetTextureDimensions(SDL_Texture* texture);
		SDL_Color TexturePixelToColor(Uint8* pixels, const Vector2int& pixelPosition, const int& textureWidth);
#else
		inline float hireTimeInSeconds()
		{
			Debug::Log("Implement hireTimeInSeconds()", Debug::fixme);
			return 0;
		}
#endif /* LIB_SDL */

		std::vector<Vector2int> SortPath(const Vector2int& startPoint, const std::vector<Vector2int>& points);
		std::string CleanDecimals(const double& value); ///< Returns a string with without trailing zeroes in decimals

		std::vector<Line> PolygonToLines(const Vector2f polygon[], const int& polygonSize);
	}
}
