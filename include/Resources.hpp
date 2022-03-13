#pragma once

#include <string>
//#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Values.hpp"

namespace Birb
{
	/// Methods for loading different resources like fonts and textures
	struct Resources
	{
		static SDL_Texture* LoadTexture(const std::string& p_filePath);
		static SDL_Texture* TextSprite(const std::string& text, TTF_Font* font, const SDL_Color& color);
		static SDL_Texture* TextSprite(const std::string& text, TTF_Font* font, const SDL_Color& color, const SDL_Color& bgColor);
		static TTF_Font* 	LoadFont(const std::string& p_filePath, const int& p_fontSize);
		static Uint8* 		CopyTexturePixels(SDL_Surface* surface, int* width, int* height, int* pitch);
	};
}
