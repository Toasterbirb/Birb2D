#pragma once

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "Vector.hpp"

namespace SDL
{
	class Window
	{
	public:
		Window(const std::string& title, const Birb::Vector2int& window_dimensions, SDL_Window* win, SDL_Renderer* renderer, const int& refresh_rate, const bool& resizable);

	private:
		void InitSDL();
		void InitSDL_image();
	};
}
