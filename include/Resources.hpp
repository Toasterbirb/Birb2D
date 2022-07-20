#pragma once

#include <string>
#include "SDL.hpp"

#include "Values.hpp"

namespace Birb
{
	/// Methods for loading different resources like fonts and textures
	struct Resources
	{
#ifdef LIB_SDL
		static SDL_Texture* LoadTexture(const std::string& p_filePath);
		static SDL_Texture* TextSprite(const std::string& text, TTF_Font* font, const SDL_Color& color);
		static SDL_Texture* TextSprite(const std::string& text, TTF_Font* font, const SDL_Color& color, const SDL_Color& bgColor);
		static Uint8* 		CopyTexturePixels(SDL_Surface* surface, int* width, int* height, int* pitch);
#endif /* LIB_SDL */
	};
}
