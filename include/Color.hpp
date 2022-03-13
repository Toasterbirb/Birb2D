#pragma once

#include <SDL2/SDL.h>

namespace Birb
{
	struct Color
	{
		Color();
		Color(const int& r, const int& g, const int& b);
		Color(const int& r, const int& g, const int& b, const int& a);
		Color(const int& hex);

		SDL_Color sdl() const; ///< Convert Color to SDL_Color

		Uint8 r, g, b, a;

		bool operator==(const Color& other) const
		{
			return 	(r == other.r
					&& g == other.g
					&& b == other.b
					&& a == other.a);
		}
	};
}
