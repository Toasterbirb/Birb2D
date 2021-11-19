#pragma once
#include "../vendor/SDL2/SDL.h"
#include "../vendor/SDL2/SDL_ttf.h"
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string.h>

class Font
{
public:
	//Font(TTF_Font* p_font, SDL_Color p_color, int p_size);
	Font();
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
