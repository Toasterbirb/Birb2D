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
	Window::Window()
	{
#ifdef LIB_SDL
		InitSDL();
		InitSDL_image();
#endif /* LIB_SDL */
	}

	Window::Window(const std::string& p_title, const Vector2int& p_window_dimensions, const int& p_refresh_rate, const bool& resizable)
	:win_title(p_title), refresh_rate(p_refresh_rate), dimensions(p_window_dimensions), original_window_dimensions(p_window_dimensions)
	{
#ifdef DEBUG
		Debug::Log("Creating window '" + win_title + "'...");
#endif

#ifdef LIB_SDL
		/* Create a new window and initialize stuff for it */
		InitSDL();
		InitSDL_image();

		if (resizable)
			win = SDL_CreateWindow(p_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_window_dimensions.x, p_window_dimensions.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		else
			win = SDL_CreateWindow(p_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_window_dimensions.x, p_window_dimensions.y, SDL_WINDOW_SHOWN);

		if (win == NULL)
		{
			Debug::Log("Window failed to init: " + (std::string)SDL_GetError(), Debug::error);
			exit(1);
		}

		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			Debug::Log("Renderer failed to init: " + (std::string)SDL_GetError(), Debug::error);
			exit(1);
		}

		/* Set some global rendering variables */
		Global::RenderVars::MainWindow 	= win;
		Global::RenderVars::Renderer 	= renderer;
#else /* LIB_SDL */
		Debug::Log("Most parts of the window system aren't implemented without SDL", Debug::fixme);
#endif /* LIB_SDL */

		Global::RenderVars::RefreshRate = refresh_rate;

#ifdef DEBUG
		Debug::Log("Window '" + win_title + "' created successfully!");
#endif
	}

	Window::~Window()
	{
		Cleanup();
	}

#ifdef LIB_SDL
	void Window::InitSDL()
	{
		/* Check if SDL has already been initialized */
		if (Global::IsInit::SDL)
			return;

#ifdef DEBUG
		if (Birb::Diagnostics::Debugging::InitMessages)
			Debug::Log("Initializing SDL...");
#endif

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) > 0)
		{
			Debug::Log("SDL Init failed: " + (std::string)SDL_GetError(), Debug::error);
			exit(2);
		}
		else
		{
			Global::IsInit::SDL = true;
		}
	}

	void Window::InitSDL_image()
	{
		/* Check if SDL_image has already been initialized */
		if (Global::IsInit::SDL_image)
			return;

#ifdef DEBUG
		if (Birb::Diagnostics::Debugging::InitMessages)
			Debug::Log("Initializing SDL_image...");
#endif

		if (!(IMG_Init(IMG_INIT_PNG)))
		{
			Debug::Log("IMG_Init has failed" + (std::string)SDL_GetError(), Debug::error);
			exit(2);
		}
		else
		{
			Global::IsInit::SDL_image = true;
		}
	}
#endif /* LIB_SDL */

	void Window::Cleanup()
	{
#ifdef LIB_SDL
#ifdef DEBUG
		Debug::Log("Starting window cleanup for '" + win_title + "'...");
#endif /* DEBUG */
		SDL_DestroyWindow(win);

		/* FIXME: There's some sort of memory leak with SDL_Renderer. Destroying the renderer
		 * causes heck of a lot of valgrind errors
		 * Ref: https://stackoverflow.com/questions/20823886/sdl2-memory-leaks-on-sdl-destroyrenderer
		 *
		 * Also, this deconstructor is getting called twice in some cases for some weird reason */

		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
		SDL_DestroyRenderer(renderer);

		/* Also de-initialize SDL_Mixer if audio has been used */
		if (Global::IsInit::SDL_mixer)
		{
			Mix_Quit();
			Global::IsInit::SDL_mixer = false;
		}

		Global::IsInit::SDL = false;
		Global::IsInit::SDL_image = false;
		Global::IsInit::SDL_ttf = false;

		Global::RenderVars::MainWindow = NULL;
		Global::RenderVars::Renderer = NULL;
#endif

#ifdef DEBUG
		Debug::Log("Window '" + win_title + "' destroyed!");
#endif /* DEBUG */
	}

	void Window::Clear()
	{
		/* Clear the window renderer. Call before rendering stuff */
#ifdef LIB_SDL
		SDL_RenderClear(Global::RenderVars::Renderer);
#endif /* LIB_SDL */
	}

	void Window::Display()
	{
#ifdef LIB_SDL
		SDL_RenderPresent(Global::RenderVars::Renderer);
#endif /* LIB_SDL */
	}

	Vector2int Window::CursorPosition() const
	{
		Vector2int pos;
#ifdef LIB_SDL
		SDL_GetMouseState(&pos.x, &pos.y);
#else /* LIB_SDL */
		Debug::Log("CursorPosition() not implemented", Debug::fixme);
#endif /* LIB_SDL */
		return pos;
	}

	bool Window::CursorInRect(const Rect& rect) const
	{
		Vector2int cursorPos = CursorPosition();

		if (cursorPos.x > rect.x && cursorPos.x < rect.x + rect.w)
			if (cursorPos.y > rect.y && cursorPos.y < rect.y + rect.h)
				return true;

		return false;
	}

	void Window::SetWindowSize(const Vector2int& dimensions)
	{
#ifdef LIB_SDL
		SDL_SetWindowSize(win, dimensions.x, dimensions.y);
#endif /* LIB_SDL */
		this->dimensions = dimensions;
	}

	Vector2f Window::window_dimensions_multiplier()
	{
		return Vector2f((float)dimensions.x / (float)original_window_dimensions.x,
						(float)dimensions.y / (float)original_window_dimensions.y);
	}

#ifdef LIB_SDL
	void Window::EventTick(const SDL_Event& event, bool* GameRunning)
	{
		switch (event.type)
		{
			/* Handle window resizing */
			case (SDL_WINDOWEVENT):
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
					SetWindowSize(Vector2int(event.window.data1, event.window.data2));
				break;

			case (SDL_QUIT):
				Debug::Log("Quitting...");
				*GameRunning = false;
				break;

			default:
				break;
		}
	}
#endif /* LIB_SDL */

	bool Window::PollEvents()
	{
#ifdef LIB_SDL
		return (SDL_PollEvent(&event) != 0);
#else /* LIB_SDL */
		// TODO: Implement event polling without SDL
		Debug::Log("Event polling not implemented", Debug::fixme);
		return false;
#endif /* LIB_SDL */
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
