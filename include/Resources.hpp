#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <string>
#endif

#include "SDL.hpp"

namespace Birb
{
	class Color;
	class Font;

	/// Methods for loading different resources like fonts and textures
	struct Resources
	{
		static SDL_Texture* LoadTexture(const std::string& p_filePath);
		static SDL_Texture* TextSprite(const std::string& text, const Font& font, const Color& color, int wrapLength = 0);
		static SDL_Texture* TextSprite(const std::string& text, const Font& font, const Color& color, const Color& bgColor, const int& wrapLength = 0);
		static Uint8* 		CopyTexturePixels(SDL_Surface* surface, int* width, int* height, int* pitch);
	};
}
