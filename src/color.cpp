#include "Color.hpp"
#include "Math.hpp"
#include "Vector/Vector3.hpp"
#include "Vector/Vector3Int.hpp"
#include <iostream>

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
	{
		this->r = Math::Clamp(r, 0, 255);
		this->g = Math::Clamp(g, 0, 255);
		this->b = Math::Clamp(b, 0, 255);
		a = 255;
	}

	Color::Color(const int& r, const int& g, const int& b, const int& a)
	{
		this->r = Math::Clamp(r, 0, 255);
		this->g = Math::Clamp(g, 0, 255);
		this->b = Math::Clamp(b, 0, 255);
		this->a = Math::Clamp(a, 0, 255);
	}


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
		int temp_r = r + delta;
		r = Math::Clamp(temp_r, 0, 255);

		int temp_g = g + delta;
		g = Math::Clamp(temp_g, 0, 255);

		int temp_b = b + delta;
		b = Math::Clamp(temp_b, 0, 255);
	}

	std::ostream& operator<<(std::ostream& stream, const Color& other)
	{
		stream << static_cast<short>(other.r) << ", " << static_cast<short>(other.g) << ", " << static_cast<short>(other.b) << ", " << static_cast<short>(other.a);
		return stream;
	}
}
