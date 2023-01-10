#include "Texture.hpp"
#include "Logger.hpp"
#include "Values.hpp"
#include "Utils.hpp"
#include "Resources.hpp"

namespace Birb
{
	Texture::Texture()
	{
		textureLoaded = false;
		texture_dimensions = Vector2Int(0, 0);
	}

	Texture::Texture(const std::string& filePath)
	{
		LoadTexture(filePath);
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

		// FIXME Get rid of this code when its not *needed* any longer
		//SDL_Surface* surface = IMG_Load(resource_path.c_str());
		//if (surface == NULL)
		//{
		//	Debug::Log("Failed to load image [" + resource_path + "]: " + static_cast<std::string>(SDL_GetError()), Debug::error);
		//	return false;
		//}

		/* Create a texture from the surface pixels */
		//this->sdlTex = SDL_CreateTextureFromSurface(Global::RenderVars::Renderer, surface);
		this->sdlTex = Resources::LoadTexture(filePath);

		//SDL_FreeSurface(surface);

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
			texture_dimensions = utils::GetTextureDimensions(sdlTex);
		else
			texture_dimensions = Vector2Int(0, 0);
	}
}
