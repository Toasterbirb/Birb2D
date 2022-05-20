#pragma once
#pragma GCC diagnostic ignored "-Wunused-function"

#ifdef LIB_SDL
#include <SDL2/SDL.h>
#else
#include <Logger.hpp>
#endif

#include <chrono>
#include <iostream>
#include <cstdlib>
#include <math.h>

#include "Math.hpp"
#include "Line.hpp"

namespace Birb
{
	namespace Utils
	{

#ifdef LIB_SDL
		Vector2int GetTextureDimensions(SDL_Texture* texture);
		SDL_Color TexturePixelToColor(Uint8* pixels, const Vector2int& pixelPosition, const int& textureWidth);
#endif /* LIB_SDL */

		std::string CleanDecimals(const double& value); ///< Returns a string with without trailing zeroes in decimals
		std::vector<Vector2int> SortPath(const Vector2int& startPoint, const std::vector<Vector2int>& points);
		std::vector<Line> PolygonToLines(const Vector2f polygon[], const int& polygonSize);

		void Sleep(const int& ms); ///< Puts the thread to sleep for give amount of time
	}
}
