#include "Texture.hpp"
#include "Logger.hpp"
#include "Values.hpp"
#include "Renderwindow.hpp"

namespace Birb
{
	Texture::Texture()
	{
		textureLoaded = false;
	}

	Texture::Texture(const std::string& filePath)
	{
		LoadTexture(filePath);
	}

	//Texture::~Texture()
	//{
	//	SDL_DestroyTexture(sdlTex);
	//}

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

	SDL_Texture* Texture::sdlTexture() const
	{
		return this->sdlTex;
	}

	void Texture::Destroy()
	{
		SDL_DestroyTexture(sdlTex);
	}

	Vector2int Texture::dimensions() const
	{
		return texture_dimensions;
	}
}
