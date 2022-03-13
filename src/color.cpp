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

	Color::Color(const int& hex)
	{
		r = (hex & 0xff0000) >> 16;
		g = (hex & 0xff00) >> 8;
		b = (hex & 0xff) >> 0;
		a = 255;
	}

	SDL_Color Color::sdl() const
	{
		SDL_Color color = { r, g, b, a };
		return color;
	}
}
