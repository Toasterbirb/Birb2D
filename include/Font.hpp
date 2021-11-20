#pragma once

#ifndef PLATFORM_WIN
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#else
#include "../vendor/SDL2_win/SDL2/x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../vendor/SDL2_win/SDL2_ttf-2.0.15/x86_64-w64-mingw32/include/SDL2/SDL_ttf.h"
#endif

#include <iostream>
#include <string.h>

namespace Birb2D
{
	class Font
	{
	public:
		Font();
		Font(TTF_Font* p_font, SDL_Color p_color, int p_size);
		Font(std::string p_fontPath, SDL_Color p_color, int p_size);
		Font(std::string p_fontPath, int p_size);

		int getSize();
		SDL_Color getColor();
		TTF_Font* getTTFFont();

	private:
		int size;
		std::string fontPath;
		TTF_Font* ttf_font;
		SDL_Color color;
	};
}

