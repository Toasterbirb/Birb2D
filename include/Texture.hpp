#pragma once

#include <SDL2/SDL_image.h>
#include <string>

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

	private:
		SDL_Texture* sdlTex;
		bool textureLoaded;
	};
}
