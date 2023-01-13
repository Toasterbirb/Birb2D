#pragma once

#include "Math.hpp"
#include "SDL.hpp"
#include <iosfwd>

namespace Birb
{
	struct Vector3;
	struct Vector3Int;

	struct Color
	{
		constexpr Color()
		:r(0), g(0), b(0), a(255)
		{}

		/* Int constructors */
		constexpr Color(const int& r, const int& g, const int& b)
		:r(Math::Clamp(r, 0, 255)), g(Math::Clamp(g, 0, 255)), b(Math::Clamp(b, 0, 255)), a(255) {}

		constexpr Color(const int& r, const int& g, const int& b, const int& a)
		:r(Math::Clamp(r, 0, 255)), g(Math::Clamp(g, 0, 255)), b(Math::Clamp(b, 0, 255)), a(Math::Clamp(a, 0, 255)) {}

		/* Float constructors */
		constexpr Color(const float& r, const float& g, const float& b)
		:r(static_cast<int>(std::round(Math::Lerp(0, 255, r)))),
		g(static_cast<int>(std::round(Math::Lerp(0, 255, g)))),
		b(static_cast<int>(std::round(Math::Lerp(0, 255, b)))), a(255) {}

		constexpr Color(const float& r, const float& g, const float& b, const float& a)
		:r(static_cast<int>(std::round(Math::Lerp(0, 255, r)))),
		g(static_cast<int>(std::round(Math::Lerp(0, 255, g)))),
		b(static_cast<int>(std::round(Math::Lerp(0, 255, b)))),
		a(static_cast<int>(std::round(Math::Lerp(0, 255, a)))) {}

		/* Vector3 constructors */
		/// Uses values between 0 - 255
		constexpr Color(const Vector3Int &rgb)
		:r(rgb.x), g(rgb.y), b(rgb.z), a(255) {}

		/// Uses values between 0.0 - 1.0
		constexpr Color(const Vector3 &rgb)
		:r(static_cast<int>(std::round(Math::Lerp(0, 255, rgb.x)))),
		g(static_cast<int>(std::round(Math::Lerp(0, 255, rgb.y)))),
		b(static_cast<int>(std::round(Math::Lerp(0, 255, rgb.z)))), a(255) {}

		constexpr Color(const SDL_Color& sdl_color)
		:r(sdl_color.r), g(sdl_color.g), b(sdl_color.b), a(sdl_color.a) {}

		constexpr Color(const int& hex)
		:r((hex & 0xff0000) >> 16), g((hex & 0xff00) >> 8), b((hex & 0xff) >> 0), a(255)
		{}

		SDL_Color sdl() const; ///< Convert Color to SDL_Color
		Uint8 r, g, b, a;

		void ChangeIntensity(const int& delta);


		constexpr bool operator==(const Color& other) const
		{
			return 	(r == other.r
					&& g == other.g
					&& b == other.b
					&& a == other.a);
		}

		constexpr Color operator+(const Color& other) const
		{
			return Color(this->r + other.r, this->g + other.g, this->b + other.b, this->a + other.a);
		}

		constexpr Color operator-(const Color& other) const
		{
			return Color(this->r - other.r, this->g - other.g, this->b - other.b, this->a - other.a);
		}

		constexpr Color operator*(const Color& other) const
		{
			return Color(this->r * other.r, this->g * other.g, this->b * other.b, this->a * other.a);
		}

		constexpr Color operator/(const Color& other) const
		{
			return Color(this->r / other.r, this->g / other.g, this->b / other.b, this->a / other.a);
		}
	};

	std::ostream& operator<<(std::ostream& stream, const Color& other);

	namespace Colors
	{
		static Color White =        { 255, 	255, 	255, 	255 };
		static Color Black =        { 0, 	0, 		0, 		255 };
		static Color Red =          { 255, 	0, 		0, 		255 };
		static Color Green =        { 0, 	255, 	0, 		255 };
		static Color Blue =         { 0, 	0, 		255, 	255 };
		static Color Yellow =       { 255, 	255, 	0, 		255 };
		static Color DarkGray =     { 60, 	60, 	60, 	255 };
		static Color LightGray =    { 180, 	180, 	180, 	255 };

		namespace Nord
		{
			namespace PolarNight
			{
				static Color nord0 = { 0x2e3440 };
				static Color nord1 = { 0x3b4252 };
				static Color nord2 = { 0x434c5e };
				static Color nord3 = { 0x4c566a };
			}

			namespace SnowStorm
			{
				static Color nord4 = { 0xd8dee9 };
				static Color nord5 = { 0xe5e9f0 };
				static Color nord6 = { 0xeceff4 };
			}

			namespace Frost
			{
				static Color nord7 	= { 0x8fbcbb };
				static Color nord8 	= { 0x88c0d0 };
				static Color nord9 	= { 0x81a1c1 };
				static Color nord10 = { 0x5e81ac };
			}

			namespace Aurora
			{
				static Color nord11 = { 0xbf616a }; ///< Red
				static Color nord12 = { 0xd08770 }; ///< Orange
				static Color nord13 = { 0xebcb8b }; ///< Yellow
				static Color nord14 = { 0xa3be8c }; ///< Green
				static Color nord15 = { 0xb48ead }; ///< Purple
			}
		}
	}
}
