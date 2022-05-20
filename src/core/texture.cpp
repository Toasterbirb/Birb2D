#include "Texture.hpp"
#include "Logger.hpp"
#include "Values.hpp"
#include "Renderwindow.hpp"

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
#ifdef LIB_SDL
		if (textureLoaded)
			texture_dimensions = utils::GetTextureDimensions(sdlTex);
		else
			texture_dimensions = Vector2int(0, 0);
#else
		// TODO: Figure out a way to get texture dimensions without SDL
		Debug::Log("GetTextureDimensions() without SDL missing", Debug::fixme);
#endif /* LIB_SDL */
	}

	bool Texture::LoadTexture(const std::string& filePath)
	{
#ifdef LIB_SDL
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
#else
		// TODO: Texture loading without SDL
		Debug::Log("Texture loading without SDL not implemented...", Debug::fixme);
		return false;
#endif /* LIB_SDL */
	}

#ifdef LIB_SDL
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
#endif /* LIB_SDL */

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
