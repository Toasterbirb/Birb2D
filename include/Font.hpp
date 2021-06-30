#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Font
{
public:
	Font(TTF_Font* p_font, SDL_Color p_color, int p_size);

	int getSize();
	SDL_Color getColor();
	TTF_Font* getTTFFont();

private:
	int size;
	TTF_Font* ttf_font;
	SDL_Color color;
};
