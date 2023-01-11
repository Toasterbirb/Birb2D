#include "Texture.hpp"
#include "Logger.hpp"
#include "Values.hpp"
#include "Utils.hpp"
#include "Resources.hpp"

namespace Birb
{
	Texture::Texture()
	{
		textureLoaded 		= false;
		texture_dimensions 	= Vector2Int(0, 0);
		sdlTex 				= nullptr;
	}

	Texture::Texture(const std::string& filePath)
	{
		LoadTexture(filePath);
	}

	Texture::Texture(SDL_Texture* sdlTexture)
	:sdlTex(sdlTexture)
	{
		texture_dimensions = GetTextureDimensions(sdlTexture);
		textureLoaded = true; /* Assuming the sdlTexture is valid */
	}

	bool Texture::LoadTexture(const std::string& filePath)
	{
		this->sdlTex = NULL;

		this->sdlTex = Resources::LoadTexture(filePath);

		textureLoaded = true;
		UpdateDimensions();

		return true;
	}

	SDL_Texture* Texture::sdlTexture() const
	{
		return this->sdlTex;
	}

	bool Texture::CreateFromSurface(SDL_Renderer* renderer, SDL_Surface* surface)
	{
		this->sdlTex = SDL_CreateTextureFromSurface(renderer, surface);

		if (sdlTex == nullptr)
		{
			Debug::Log("Error creating texture from surface: " + static_cast<std::string>(SDL_GetError()), Debug::error);
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
		SDL_DestroyTexture(sdlTex);
	}

	Vector2Int Texture::dimensions() const
	{
		return texture_dimensions;
	}

	void Texture::UpdateDimensions()
	{
		if (textureLoaded)
			texture_dimensions = GetTextureDimensions(sdlTex);
		else
			texture_dimensions = Vector2Int(0, 0);
	}

	Vector2Int Texture::GetTextureDimensions(SDL_Texture* texture)
	{
		Vector2Int result;
		if (SDL_QueryTexture(texture, NULL, NULL, &result.x, &result.y) < 0)
		{
			Debug::Log("Couldn't query for texture dimensions: " + std::string(SDL_GetError()), Debug::Type::warning);
			return Vector2Int(0, 0);
		}
		return result;
	}
}
