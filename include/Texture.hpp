#pragma once

#include <SDL_image.h>

#include "STD.hpp"
#include "Vector.hpp"

namespace Birb
{
	class Texture
	{
	public:
		Texture();
		Texture(const std::string& filePath);
		Texture(SDL_Texture* sdlTexture); ///< Initialize with a SDL_Texture
		//~Texture();

		bool LoadTexture(const std::string& filePath);
		bool isLoaded() const;
		void Destroy();

		Vector2int dimensions() const;

		SDL_Texture* sdlTexture() const;
		bool CreateFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);

		bool operator==(const Texture& other) const
		{
			return (texture_dimensions == other.texture_dimensions
					&& textureLoaded == other.textureLoaded
					&& sdlTex == other.sdlTex);
		}


	private:
		Vector2int texture_dimensions;
		SDL_Texture* sdlTex;
		bool textureLoaded;
	};
}
