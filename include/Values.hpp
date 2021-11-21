#pragma once
#pragma GCC diagnostic ignored "-Wunused-variable"

#ifndef PLATFORM_WIN
#include <SDL2/SDL.h>
#else
#include "../vendor/SDL2_win/SDL2/x86_64-w64-mingw32/include/SDL2/SDL.h"
#endif

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