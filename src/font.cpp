#include "../include/Font.hpp"

Font::Font(TTF_Font* p_font, SDL_Color p_color, int p_size)
:size(p_size), ttf_font(p_font), color(p_color)
{

}

int Font::getSize()
{
	return size;
}

SDL_Color Font::getColor()
{
	return color;
}

TTF_Font* Font::getTTFFont()
{
	return ttf_font;
}
