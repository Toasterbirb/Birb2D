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
	struct Asset;

	/// Methods for loading different resources like fonts and textures
	struct Resources
	{
		static SDL_Texture* LoadTexture(const std::string& p_filePath);

		/// Access bundled assets from memory
		static SDL_Texture* LoadTextureFromMem(const std::string& file_path);

		/// Convert SDL_RWops to a texture from an asset object
		static SDL_Texture* LoadTextureFromMem(const Asset& asset);

		static SDL_Texture* TextSprite(const std::string& text, const Font& font, const Color& color, int wrapLength = 0);
		static SDL_Texture* TextSprite(const std::string& text, const Font& font, const Color& color, const Color& bgColor, int wrapLength = 0);
		static Uint8* 		CopyTexturePixels(SDL_Surface* surface, int* width, int* height, int* pitch);
	};
}
