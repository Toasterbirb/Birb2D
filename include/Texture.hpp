#pragma once

#include "SDL.hpp"

#include <string>
#include "Vector.hpp"

namespace Birb
{
	class Texture
	{
	public:
		Texture();
		Texture(const std::string& filePath);
		//~Texture();

		bool LoadTexture(const std::string& filePath);
		bool isLoaded() const;
		void Destroy();

		Vector2int dimensions() const;
#ifdef LIB_SDL
		SDL_Texture* sdlTexture() const;
		bool CreateFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);
#endif

	private:
		Vector2int texture_dimensions;
#ifdef LIB_SDL
		SDL_Texture* sdlTex;
#endif
		bool textureLoaded;
	};
}
