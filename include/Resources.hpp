#pragma once

#include <string>

#ifdef LIB_SDL
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#endif

#include "Font.hpp"
#include "Values.hpp"

namespace Birb
{
	/// Methods for loading different resources like fonts and textures
	struct Resources
	{
#ifdef LIB_SDL
		static SDL_Texture* LoadTexture(const std::string& p_filePath);
		static SDL_Texture* TextSprite(const std::string& text, const Font& font, const Color& color, int wrapLength = 0);
		static SDL_Texture* TextSprite(const std::string& text, const Font& font, const Color& color, const Color& bgColor);
		static Uint8* 		CopyTexturePixels(SDL_Surface* surface, int* width, int* height, int* pitch);
#endif /* LIB_SDL */
	};
}
