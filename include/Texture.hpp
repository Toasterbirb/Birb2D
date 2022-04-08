#pragma once

#include <SDL2/SDL_image.h>
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
		bool CreateFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);
		bool isLoaded() const;
		SDL_Texture* sdlTexture() const;
		void Destroy();
		Vector2int dimensions() const;

	private:
		Vector2int texture_dimensions;
		SDL_Texture* sdlTex;
		bool textureLoaded;
	};
}
