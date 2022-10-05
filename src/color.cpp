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


	Color::Color(const float& r, const float& g, const float& b)
	{
		this->r = static_cast<int>(std::round(Math::Lerp(0, 255, r)));
		this->g = static_cast<int>(std::round(Math::Lerp(0, 255, g)));
		this->b = static_cast<int>(std::round(Math::Lerp(0, 255, b)));
		a = 255;
	}

	Color::Color(const float& r, const float& g, const float& b, const float& a)
	{
		this->r = static_cast<int>(std::round(Math::Lerp(0, 255, r)));
		this->g = static_cast<int>(std::round(Math::Lerp(0, 255, g)));
		this->b = static_cast<int>(std::round(Math::Lerp(0, 255, b)));
		this->a = static_cast<int>(std::round(Math::Lerp(0, 255, a)));
	}

	Color::Color(const Vector3Int& rgb)
	:r(rgb.x), g(rgb.y), b(rgb.z)
	{
		a = 255;
	}

	Color::Color(const Vector3& rgb)
	{
		this->r = static_cast<int>(std::round(Math::Lerp(0, 255, rgb.x)));
		this->g = static_cast<int>(std::round(Math::Lerp(0, 255, rgb.y)));
		this->b = static_cast<int>(std::round(Math::Lerp(0, 255, rgb.z)));
		a = 255;
	}

	Color::Color(const SDL_Color& sdl_color)
	{
		r = sdl_color.r;
		g = sdl_color.g;
		b = sdl_color.b;
		a = sdl_color.a;
	}

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

	void Color::ChangeIntensity(const int& delta)
	{
		r += delta;
		r = Math::Clamp(r, 0, 255);

		g += delta;
		g = Math::Clamp(g, 0, 255);

		b += delta;
		b = Math::Clamp(b, 0, 255);
	}
}
