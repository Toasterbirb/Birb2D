#pragma once

#include "SDL.hpp"

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

		void ChangeIntensity(const int& delta);


		bool operator==(const Color& other) const
		{
			return 	(r == other.r
					&& g == other.g
					&& b == other.b
					&& a == other.a);
		}

	};

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
	}
}
