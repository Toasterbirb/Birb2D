#include "Widgets.hpp"
#include "Font.hpp"
#include "Values.hpp"
#include "Logger.hpp"

Birb2D::Font::Font()
{
	Birb2D::RenderWindow::InitSDL_ttf();

	color = Colors::White;
	ttf_font = TTF_OpenFont("../res/fonts/manaspace/manaspc.ttf", 32);
}

Birb2D::Font::Font(std::string p_fontPath, SDL_Color p_color, int p_size)
:size(p_size), fontPath(p_fontPath), color(p_color)
{
	Birb2D::RenderWindow::InitSDL_ttf();

	color = p_color;
	ttf_font = TTF_OpenFont(p_fontPath.c_str(), p_size);
	if (ttf_font == NULL)
		Debug::Log("Error opening font [" + p_fontPath + "]. Size: " + std::to_string(size) + ". Color: (" + std::to_string(color.r) + ", " + std::to_string(color.g) + ", " + std::to_string(color.b) + ", " + std::to_string(color.a) + "). Error: " + (std::string)TTF_GetError(), Debug::error);
}

Birb2D::Font::Font(std::string p_fontPath, int p_size)
:size(p_size), fontPath(p_fontPath)
{
	Birb2D::RenderWindow::InitSDL_ttf();

	color = Colors::White;
	ttf_font = TTF_OpenFont(p_fontPath.c_str(), p_size);
	if (ttf_font == NULL)
		Debug::Log("Error opening font [" + p_fontPath + "]. Size: " + std::to_string(size) + ". Error: " + (std::string)TTF_GetError(), Debug::error);
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
