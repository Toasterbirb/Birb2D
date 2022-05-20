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

#ifdef LIB_SDL
	SDL_Color Color::sdl() const
	{
		SDL_Color color = { r, g, b, a };
		return color;
	}
#endif /* LIB_SDL */

	void Color::ChangeIntensity(const int& delta)
	{
		if (delta > 0)
		{
			// Increase color intensity

			// Red
			if (r + delta > 255)
				r = 255;
			else
				r += delta;

			// Green
			if (g + delta > 255)
				g = 255;
			else
				g += delta;

			// Blue
			if (b + delta > 255)
				b = 255;
			else
				b += delta;
		}
		else
		{
			// Decrease color intensity

			// Red
			if (r + delta < 0)
				r = 0;
			else
				r += delta;

			// Green
			if (g + delta < 0)
				g = 0;
			else
				g += delta;

			// Blue
			if (b + delta < 0)
				b = 0;
			else
				b += delta;
		}
	}
}
