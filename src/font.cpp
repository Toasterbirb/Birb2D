#include "../include/Widgets.hpp"
#include "../vendor/SDL2/SDL.h"
#include "../vendor/SDL2/SDL_ttf.h"
#include "../include/Font.hpp"

Font::Font()
{
	color = Widget::Colors::White;
	ttf_font = TTF_OpenFont("../res/fonts/manaspace/manaspc.ttf", 32);
}

Font::Font(std::string p_fontPath, SDL_Color p_color, int p_size)
:size(p_size), fontPath(p_fontPath), color(p_color)
{
	ttf_font = TTF_OpenFont(p_fontPath.c_str(), p_size);
}

Font::Font(std::string p_fontPath, int p_size)
:size(p_size), fontPath(p_fontPath)
{
	ttf_font = TTF_OpenFont(p_fontPath.c_str(), p_size);
	color = Widget::Colors::White;
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
