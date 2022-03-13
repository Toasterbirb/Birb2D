#include "Color.hpp"

namespace Birb
{
	Color::Color()
	{
		r = 0;
		g = 0;
		b = 0;
		a = 255;
	}

	Color::Color(const int& r, const int& g, const int& b)
	:r(r), g(g), b(b)
	{
		a = 255;
	}

	Color::Color(const int& r, const int& g, const int& b, const int& a)
	:r(r), g(g), b(b), a(a)
	{}

	SDL_Color Color::sdl() const
	{
		SDL_Color color = { r, g, b, a };
		return color;
	}
}
