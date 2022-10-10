#include "Resources.hpp"
#include "Logger.hpp"
#include "microprofile.h"

#define PROFILER_GROUP "Resources"
#define PROFILER_COLOR MP_RED

namespace Birb
{
	SDL_Texture* Resources::LoadTexture(const std::string& p_filePath)
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Load SDL_Texture", PROFILER_COLOR);

		SDL_Texture* texture = NULL;
		texture = IMG_LoadTexture(Global::RenderVars::Renderer, p_filePath.c_str());

		if (texture == NULL)
			Debug::Log("Failed to load texture [" + p_filePath + "]: " + static_cast<std::string>(SDL_GetError()), Debug::error);

		return texture;
	}

	Uint8* Resources::CopyTexturePixels(
        SDL_Surface* surface, // surface to take pixels from
        int* width,
        int* height,
        int* pitch)
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Copy texture pixels to Uint8 array", PROFILER_COLOR);

		Uint8* pixels = 0;
		SDL_Surface* tmpSurface = 0;
		SDL_Texture* texture = 0;
		int sizeInBytes = 0;
		void* tmpPixels = 0;
		int tmpPitch = 0;
		Uint32 pixelFormat = SDL_GetWindowPixelFormat(Global::RenderVars::MainWindow);

		tmpSurface = SDL_ConvertSurfaceFormat(surface, pixelFormat, 0);
		if (tmpSurface)
			texture = SDL_CreateTexture(Global::RenderVars::Renderer, pixelFormat, SDL_TEXTUREACCESS_STREAMING, tmpSurface->w, tmpSurface->h);

		if (texture)
		{
			if (width)
				*width = tmpSurface->w;

			if (height)
				*height = tmpSurface->h;

			if (pitch)
				*pitch = tmpSurface->pitch;

			sizeInBytes = tmpSurface->pitch * tmpSurface->h;
			pixels = static_cast<Uint8*>(malloc( sizeInBytes ));
			SDL_LockTexture(texture, 0, &tmpPixels, &tmpPitch);
			memcpy(pixels, tmpSurface->pixels, sizeInBytes);
			SDL_UnlockTexture(texture);
		}

		/* Cleanup stuff */
		if (texture)
			SDL_DestroyTexture(texture);

		if (tmpSurface)
			SDL_FreeSurface(tmpSurface);

		return pixels;
	}


	SDL_Texture* Resources::TextSprite(const std::string& text, const Font& font, const Color& color, int wrapLength)
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Render text sprite", PROFILER_COLOR);

		/* Check if the arguments are valid */
		if (!font.isLoaded())
		{
			Debug::Log("Tried to render text with invalid font!");
			return NULL;
		}

		SDL_Surface* surface;

		// wrapLength of 0 is meant to only wrap with '\n', but seems to not work on some systems
		// Disabling for now, as this breaks text rendering.
		// FIXME: Enable when this feature is supported
		//if (wrapLength != 0) {
			surface = TTF_RenderText_Blended_Wrapped(font.ttf(), text.c_str(), color.sdl(), wrapLength);
		//} else {
		//	surface = TTF_RenderText_Blended(font.ttf(), text.c_str(), color.sdl());
		//}

		if (surface == nullptr)
			Debug::Log("Error creating SDL_Surface. Text: " + static_cast<std::string>(text) + ". SDL Error: " + static_cast<std::string>(SDL_GetError()), Debug::error);

		SDL_Texture* texture = SDL_CreateTextureFromSurface(Global::RenderVars::Renderer, surface);
		if (texture == nullptr)
			Debug::Log("Error creating texture from surface: " + static_cast<std::string>(SDL_GetError()), Debug::error);

		SDL_FreeSurface(surface);
		return texture;
	}

	SDL_Texture* Resources::TextSprite(const std::string& text, const Font& font, const Color& color, const Color& bgColor)
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Render text sprite with background color", PROFILER_COLOR);

		/* Check if the arguments are valid */
		if (!font.isLoaded())
		{
			Debug::Log("Tried to render text with invalid font!");
			return NULL;
		}

		SDL_Surface* surface = TTF_RenderText_Shaded(font.ttf(), text.c_str(), color.sdl(), bgColor.sdl());
		if (surface == nullptr)
			Debug::Log("Error creating SDL_Surface. Text: " + static_cast<std::string>(text) + ". SDL Error: " + static_cast<std::string>(SDL_GetError()), Debug::error);

		/* FIXME: Implement wrapping for this function too */
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Global::RenderVars::Renderer, surface);
		if (texture == nullptr)
			Debug::Log("Error creating texture from surface: " + static_cast<std::string>(SDL_GetError()), Debug::error);

		SDL_FreeSurface(surface);
		return texture;
	}
}
