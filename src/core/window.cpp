#include "Window.hpp"
#include "Render.hpp"
#include "Values.hpp"
#include "Logger.hpp"
#include "Diagnostics.hpp"

#ifdef LIB_SDL
#include <SDL2/SDL_mixer.h>
#endif

namespace Birb
{
	Window::~Window()
	{
		Cleanup();
	}

	bool Window::CursorInRect(const Rect& rect) const
	{
		Vector2int cursorPos = CursorPosition();

		if (cursorPos.x > rect.x && cursorPos.x < rect.x + rect.w)
			if (cursorPos.y > rect.y && cursorPos.y < rect.y + rect.h)
				return true;

		return false;
	}


	Vector2f Window::window_dimensions_multiplier()
	{
		return Vector2f((float)dimensions.x / (float)original_window_dimensions.x,
						(float)dimensions.y / (float)original_window_dimensions.y);
	}


	bool Window::PollEvents()
	{
#ifdef LIB_SDL
		return (SDL_PollEvent(&event) != 0);
#elif LIB_GLFW
		glfwPollEvents();
		return false;
#endif /* LIB_SDL */

		return false;
	}


#ifdef LIB_SDL
	void HandleAnimations(Entity* entity, SDL_Rect* src, SDL_Rect* dst)
	{
		Vector2int atlasPos = entity->getAtlasPosition(entity->animationComponent.frameIndex);
		src->x = atlasPos.x;
		src->y = atlasPos.y;
		src->w = entity->animationComponent.spriteSize.x;
		src->h = entity->animationComponent.spriteSize.y;

		dst->x = entity->rect.x;
		dst->y = entity->rect.y;
		dst->w = src->w * entity->localScale.x;
		dst->h = src->h * entity->localScale.y;



		/* Set the current atlas position to the next frame */
		if (entity->animationComponent.animationQueued || entity->animationComponent.loop)
		{
			if (entity->animationComponent.frameTimer.running && entity->animationComponent.frameTimer.ElapsedSeconds() >= (1.0 / entity->animationComponent.fps))
			{
				if (entity->animationComponent.frameIndex < entity->animationComponent.lastFrame)
				{
					entity->animationComponent.frameIndex++;
					entity->animationComponent.frameTimer.Start();
				}
			}
			else if (!entity->animationComponent.frameTimer.running)
			{
				/* Start the frame timer */
				entity->animationComponent.frameTimer.Start();
			}

			if (entity->animationComponent.loop && entity->animationComponent.frameIndex >= entity->animationComponent.lastFrame)
			{
				entity->animationComponent.frameIndex = 0;
			}
			else if (entity->animationComponent.animationQueued && entity->animationComponent.frameIndex >= entity->animationComponent.lastFrame)
			{
				entity->animationComponent.frameIndex = entity->animationComponent.lastFrame;
				entity->animationComponent.animationQueued = false;
			}
		}
	}
#endif /* LIB_SDL */

	void DrawProgressBar(const Entity& entity)
	{
		/* Draw progress bar background unless the bar is full */
		if (entity.progressBarComponent.value < entity.progressBarComponent.maxValue)
			Render::DrawRect(*entity.progressBarComponent.backgroundColor, entity.rect);

		/* Draw the progress bar filler box */
		Birb::Rect fillRect(entity.rect.x, entity.rect.y, (entity.progressBarComponent.value / entity.progressBarComponent.maxValue) * entity.rect.w, entity.rect.h);
		Render::DrawRect(*entity.progressBarComponent.fillColor, fillRect);

		/* Draw the progress bar outer box */
		Render::DrawRect(*entity.progressBarComponent.borderColor, entity.rect, entity.progressBarComponent.borderWidth);
	}

	bool Render::DrawEntity(Entity& entity)
	{
		if (!entity.active)
			return true;

		//if (entity.sprite == nullptr)
		//{
		//	Debug::Log("Entity '" + entity.name + "' has no sprite to render", Debug::error);
		//	return false;
		//}

		/* Check if the sprite would be even visible */
		if (entity.rect.w <= 0 || entity.rect.h <= 0)
		{
			Birb::Debug::Log("Tried to render an entity with size of <= 0", Debug::Type::warning);
			return false;
		}

#ifdef LIB_SDL
		SDL_Rect src;
		SDL_Rect dst;
#else
		Rect src;
		Rect dst;
#endif /* LIB_SDL */
		Vector2int centerPoint;

		/* Get texture data */
		int texWidth 	= 0;
		int texHeight 	= 0;

		/* Skip the texture width tests if the entity doesn't have a texture on it */
		if (entity.sprite.isLoaded())
		{
			texWidth 	= entity.sprite.dimensions().x;
			texHeight 	= entity.sprite.dimensions().y;

			if (texWidth <= 0 || texHeight <= 0)
			{
				Birb::Debug::Log("Tried to render an entity with a texture with size of <= 0", Debug::Type::warning);
				return false;
			}
		}

		if (entity.animationComponent.frameCount <= 0) /* Check if the entity has animations */
		{
			src.x = 0;
			src.y = 0;
			src.w = texWidth;
			src.h = texHeight;

			dst.x = entity.rect.x;
			dst.y = entity.rect.y;
			dst.w = entity.rect.w * entity.localScale.x;
			dst.h = entity.rect.h * entity.localScale.y;
		}
		else
		{
			/* Entity probably has an animation component */
#ifdef LIB_SDL
			HandleAnimations(&entity, &src, &dst);
#else
			// TODO: Figure out how to do animations without SDL
#endif /* LIB_SDL */
		}

		/* Check if the entity has an active progress bar component */
		if (entity.progressBarComponent.active)
		{
			/* Crop the sprite if the value of a the progress bar component is less than its max value */
			if (entity.progressBarComponent.value < entity.progressBarComponent.maxValue)
			{
				dst.x = dst.x + entity.progressBarComponent.borderWidth;
				src.w = (entity.progressBarComponent.value / entity.progressBarComponent.maxValue) * texWidth - (entity.progressBarComponent.borderWidth * 2);
			}

			DrawProgressBar(entity);
		}

		centerPoint = Vector2int((entity.rect.w * entity.localScale.x) / 2, (entity.rect.h * entity.localScale.y) / 2);

		// TODO: Figure out rendering without SDL
#ifdef LIB_SDL
		SDL_Point center = { centerPoint.x, centerPoint.y };

		/* Skip rendering the texture if one doesn't exist on the entity */
		if (entity.sprite.isLoaded() == true)
		{
			if (SDL_RenderCopyEx(Global::RenderVars::Renderer, entity.sprite.sdlTexture(), &src, &dst, entity.angle, &center, SDL_FLIP_NONE) < 0)
				Debug::Log("Error rendering [" + entity.name + ", (" + entity.rect.toString() + ")]. SDL Error: " + SDL_GetError(), Debug::error);
			else
				return true;
		}
#endif /* LIB_SDL */

		return true;
	}

}
