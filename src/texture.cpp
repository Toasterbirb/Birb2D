#include "Texture.hpp"
#include "Logger.hpp"
#include "Values.hpp"
#include "Utils.hpp"

namespace Birb
{
	Texture::Texture()
	{
		textureLoaded = false;
		texture_dimensions = Vector2int(0, 0);
	}

	Texture::Texture(const std::string& filePath)
	{
		textureLoaded = LoadTexture(filePath);

		/* If the texture was loaded successfully, get its dimensions */
		if (textureLoaded)
			texture_dimensions = utils::GetTextureDimensions(sdlTex);
		else
			texture_dimensions = Vector2int(0, 0);
	}

	Texture::Texture(SDL_Texture* sdlTexture)
	:sdlTex(sdlTexture)
	{
		texture_dimensions = utils::GetTextureDimensions(sdlTexture);
		textureLoaded = true; /* Assuming the sdlTexture is valid */
	}

	bool Texture::LoadTexture(const std::string& filePath)
	{
		this->sdlTex = NULL;

		SDL_Surface* surface = IMG_Load(filePath.c_str());
		if (surface == NULL)
		{
			Debug::Log("Failed to load image [" + filePath + "]: " + (std::string)SDL_GetError(), Debug::error);
			return false;
		}

		/* Create a texture from the surface pixels */
		this->sdlTex = SDL_CreateTextureFromSurface(Global::RenderVars::Renderer, surface);

		SDL_FreeSurface(surface);
		return true;
	}

	SDL_Texture* Texture::sdlTexture() const
	{
		return this->sdlTex;
	}

	bool Texture::CreateFromSurface(SDL_Renderer* renderer, SDL_Surface* surface)
	{
		this->sdlTex = SDL_CreateTextureFromSurface(Global::RenderVars::Renderer, surface);

		if (sdlTex == nullptr)
		{
			Debug::Log("Error creating texture from surface: " + (std::string)SDL_GetError(), Debug::error);
			return false;
		}
		else
		{
			return true;
		}
	}

	bool Texture::isLoaded() const
	{
		return textureLoaded;
	}


	void Texture::Destroy()
	{
		//SDL_DestroyTexture(sdlTex);
	}

	Vector2int Texture::dimensions() const
	{
		return texture_dimensions;
	}
}
