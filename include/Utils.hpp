#pragma once
#pragma GCC diagnostic ignored "-Wunused-function"

#ifndef DISTCC
#include "STD.hpp"
#else
#include <string>
#include <vector>
#endif

#include "SDL.hpp"
#include "Logger.hpp"


#include "Math.hpp"
#include "Line.hpp"


namespace Birb
{
	namespace utils
	{
		inline double hireTimeInSeconds()
		{
			double t = SDL_GetTicks();
			t *= 0.001f;

			return t;
		}

		SDL_Color TexturePixelToColor(Uint8* pixels, const Vector2Int& pixelPosition, int textureWidth);

		std::vector<Vector2Int> SortPath(const Vector2Int& startPoint, const std::vector<Vector2Int>& points);
		std::string CleanDecimals(double value); ///< Returns a string with without trailing zeroes in decimals

		std::vector<Line> PolygonToLines(const Vector2 polygon[], int polygonSize);

		int FlatIndex(const Vector2Int& array_position, const Vector2Int& array_dimensions); ///< Returns a 1 dimensional index for a 2 dimensional array
	}
}
