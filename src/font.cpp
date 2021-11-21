#include "../include/Widgets.hpp"
#include "../include/Font.hpp"
#include "../include/Values.hpp"
#include "../include/Logger.hpp"

Birb2D::Font::Font()
{
	color = Colors::White;
	ttf_font = TTF_OpenFont("../res/fonts/manaspace/manaspc.ttf", 32);
}

Birb2D::Font::Font(std::string p_fontPath, SDL_Color p_color, int p_size)
:size(p_size), fontPath(p_fontPath), color(p_color)
{
	color = p_color;
	ttf_font = TTF_OpenFont(p_fontPath.c_str(), p_size);
	if (ttf_font == NULL)
		Debug::Log("Error opening font [" + p_fontPath + "]: " + (std::string)TTF_GetError(), Debug::error);
}

Birb2D::Font::Font(std::string p_fontPath, int p_size)
:size(p_size), fontPath(p_fontPath)
{
	color = Colors::White;
	ttf_font = TTF_OpenFont(p_fontPath.c_str(), p_size);
	if (ttf_font == NULL)
		Debug::Log("Error opening font [" + p_fontPath + "]: " + (std::string)TTF_GetError(), Debug::error);
}

int Birb2D::Font::getSize()
{
	return size;
}

SDL_Color Birb2D::Font::getColor()
{
	return color;
}

TTF_Font* Birb2D::Font::getTTFFont()
{
	return ttf_font;
}
