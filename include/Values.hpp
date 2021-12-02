#pragma once
#pragma GCC diagnostic ignored "-Wunused-variable"

#include <SDL2/SDL.h>
#include "RenderWindow.hpp"

namespace Global
{
	namespace IsInit
	{
		static bool SDL 		= false;
		static bool SDL_ttf 	= false;
		static bool SDL_image 	= false;
	}
}

namespace Colors
{
	static SDL_Color White = 		{ 255, 255, 255, 255 };
	static SDL_Color Black = 		{ 0, 0, 0, 255 };
	static SDL_Color Red = 			{ 255, 0, 0, 255 };
	static SDL_Color Green = 		{ 0, 255, 0, 255 };
	static SDL_Color Blue = 		{ 0, 0, 255, 255 };
	static SDL_Color DarkGray = 	{ 60, 60, 60, 255 };
	static SDL_Color LightGray = 	{ 180, 180, 180, 255 };

	SDL_Color ChangeColorIntensity(SDL_Color color, int delta);
}
