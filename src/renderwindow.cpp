#include "Renderwindow.hpp"
#include "Entities/Animation.hpp"
#include "Values.hpp"
#include "Logger.hpp"
#include "Diagnostics.hpp"
#include "Physics.hpp"
#include "microprofile.h"

#define PROFILER_GROUP "Rendering"
#define PROFILER_COLOR MP_LIGHTBLUE

namespace Birb
{
	static void DrawProgressBar(const Entity& entity);
	static void HandleAnimations(Entity* entity, SDL_Rect* src, SDL_Rect* dst);

	Window::Window()
	{
		InitSDL();
		InitSDL_image();
	}

	Window::Window(const std::string& p_title, const Vector2Int& p_window_dimensions, const int& p_refresh_rate, const bool& resizable)
	:win_title(p_title), refresh_rate(p_refresh_rate), dimensions(p_window_dimensions), original_window_dimensions(p_window_dimensions)
	{

		Debug::Log("Creating window '" + win_title + "'...");

		/* Create a new window and initialize stuff for it */
		InitSDL();
		InitSDL_image();

		if (resizable)
			win = SDL_CreateWindow(p_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_window_dimensions.x, p_window_dimensions.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		else
			win = SDL_CreateWindow(p_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_window_dimensions.x, p_window_dimensions.y, SDL_WINDOW_SHOWN);

		if (win == NULL)
		{
			Debug::Log("Window failed to init: " + static_cast<std::string>(SDL_GetError()), Debug::error);
			exit(1);
		}

		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			Debug::Log("Renderer failed to init: " + static_cast<std::string>(SDL_GetError()), Debug::error);
			exit(1);
		}

		/* Set some global rendering variables */
		Global::RenderVars::RefreshRate 		= refresh_rate;
		Global::RenderVars::WindowDimensions 	= dimensions;
		Global::RenderVars::MainWindow 			= win;
		Global::RenderVars::Renderer 			= renderer;

		/* Define callback functions to some default values */
		OnWindowResize = DefaultOnWindowResize;


		Debug::Log("Window '" + win_title + "' created successfully!");
	}

	Window::~Window()
	{
		Cleanup();
	}

	void Window::InitSDL()
	{
		/* Check if SDL has already been initialized */
		if (Global::IsInit::SDL)
			return;


		if (Birb::Diagnostics::Debugging::InitMessages)
			Debug::Log("Initializing SDL...");

		if (SDL_Init(SDL_INIT_VIDEO) > 0)
		{
			Debug::Log("SDL Init failed: " + static_cast<std::string>(SDL_GetError()), Debug::error);
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


		if (Birb::Diagnostics::Debugging::InitMessages)
			Debug::Log("Initializing SDL_image...");

		if (!(IMG_Init(IMG_INIT_PNG)))
		{
			Debug::Log("IMG_Init has failed" + static_cast<std::string>(SDL_GetError()), Debug::error);
			exit(2);
		}
		else
		{
			Global::IsInit::SDL_image = true;
		}
	}

	void Window::Cleanup()
	{

		Debug::Log("Starting window cleanup for '" + win_title + "'...");

		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(win);

		SDL_QuitSubSystem(SDL_INIT_VIDEO);

		IMG_Quit();
		SDL_Quit();

		Global::IsInit::SDL = false;
		Global::IsInit::SDL_image = false;

		Global::RenderVars::MainWindow = NULL;
		Global::RenderVars::Renderer = NULL;


		Debug::Log("Window '" + win_title + "' destroyed!");
	}

	void Window::Clear()
	{
		/* Clear the window renderer. Call before rendering stuff */
		SDL_RenderClear(Global::RenderVars::Renderer);
	}

	void Window::Display()
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Window display", PROFILER_COLOR);
		SDL_RenderPresent(Global::RenderVars::Renderer);
		MicroProfileFlip(nullptr);
	}

	Vector2Int Window::CursorPosition() const
	{
		Vector2Int pos;
		SDL_GetMouseState(&pos.x, &pos.y);
		return pos;
	}

	bool Window::CursorInRect(const Rect& rect) const
	{
		return Physics::PointInRect(rect, CursorPosition());
	}

	void Window::SetWindowSize(const Vector2Int& dimensions)
	{
		SDL_SetWindowSize(win, dimensions.x, dimensions.y);
		this->dimensions = dimensions;
	}

	Vector2 Window::window_dimensions_multiplier()
	{
		return Vector2(static_cast<float>(dimensions.x) / static_cast<float>(original_window_dimensions.x),
						static_cast<float>(dimensions.y) / static_cast<float>(original_window_dimensions.y));
	}

	bool Window::PollEvents()
	{
		return (SDL_PollEvent(&event) != 0);
	}

	void Window::EventTick(const SDL_Event& event, bool* GameRunning)
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Window event tick", PROFILER_COLOR);
		switch (event.type)
		{
			/* Handle window resizing */
			case (SDL_WINDOWEVENT):
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					SetWindowSize(Vector2Int(event.window.data1, event.window.data2));
					OnWindowResize(*this);
					Global::RenderVars::WindowDimensions = dimensions;
				}
				break;

			case (SDL_QUIT):
				Debug::Log("Quitting...");
				*GameRunning = false;
				break;

			default:
				break;
		}
	}

	Input::KeyCode Window::key_event() const
	{
		return Input::EventToKeycode(this->event);
	}

	bool Window::isKeyDown() const
	{
		return (this->event.type == SDL_KEYDOWN);
	}

	bool Window::isKeyUp() const
	{
		return (this->event.type == SDL_KEYUP);
	}

	bool Window::isMouseDown() const
	{
		return (this->event.type == SDL_MOUSEBUTTONDOWN);
	}

	bool Window::isMouseUp() const
	{
		return (this->event.type == SDL_MOUSEBUTTONUP);
	}

	void Window::DefaultOnWindowResize(Window& window)
	{
		return;
	}

	void HandleAnimations(Animation* entity, SDL_Rect* src, SDL_Rect* dst)
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Handle animations", PROFILER_COLOR);
		Vector2Int atlasPos = entity->getAtlasPosition(entity->animationComponent.frameIndex);
		src->x = atlasPos.x;
		src->y = atlasPos.y;
		src->w = entity->animationComponent.spriteSize.x;
		src->h = entity->animationComponent.spriteSize.y;

		dst->x = entity->rect.x - (Global::RenderVars::CameraPosition.x * entity->world_space);
		dst->y = entity->rect.y - (Global::RenderVars::CameraPosition.y * entity->world_space);
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

	void DrawProgressBar(const Entity& entity)
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw progress bar", PROFILER_COLOR);
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
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw entity", PROFILER_COLOR);
		if (!entity.active)
			return true;

		/* Check if the sprite would be even visible */
		if (entity.rect.w <= 0 || entity.rect.h <= 0)
		{
			Birb::Debug::Log("Tried to render an entity with size of <= 0", Debug::Type::warning);
			return false;
		}

		SDL_Rect src;
		SDL_Rect dst;
		Vector2Int centerPoint;

		/* Get texture data */
		int texWidth 	= 0;
		int texHeight 	= 0;

		/* Skip the texture width tests if the entity doesn't have a texture on it */
		if (entity.sprite.isLoaded())
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Entity sprite scale calculation", PROFILER_COLOR);
			texWidth 	= entity.sprite.dimensions().x;
			texHeight 	= entity.sprite.dimensions().y;

			if (texWidth <= 0 || texHeight <= 0)
			{
				Birb::Debug::Log("Tried to render an entity with a texture with size of <= 0", Debug::Type::warning);
				return false;
			}

			if (entity.animationComponent.frameCount <= 0) /* Check if the entity has animations */
			{
				src.x = 0;
				src.y = 0;
				src.w = texWidth;
				src.h = texHeight;

				dst.x = entity.rect.x - (Global::RenderVars::CameraPosition.x * entity.world_space);
				dst.y = entity.rect.y - (Global::RenderVars::CameraPosition.y * entity.world_space);
				dst.w = entity.rect.w * entity.localScale.x;
				dst.h = entity.rect.h * entity.localScale.y;
			}
			else
			{
				/* Entity probably has an animation component */
				HandleAnimations(&entity, &src, &dst);
			}
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

			/* We are done if there isn't going to be a sprite to render */
			if (!entity.sprite.isLoaded())
				return true;
		}

		/* Skip rendering the texture if one doesn't exist on the entity */
		if (entity.sprite.isLoaded())
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw entity sprite", PROFILER_COLOR);
			centerPoint = Vector2Int((entity.rect.w * entity.localScale.x) / 2, (entity.rect.h * entity.localScale.y) / 2);
			SDL_Point center = { centerPoint.x, centerPoint.y };

			if (SDL_RenderCopyEx(Global::RenderVars::Renderer, entity.sprite.sdlTexture(), &src, &dst, entity.angle, &center, SDL_FLIP_NONE) < 0)
				Debug::Log("Error rendering [" + entity.name + ", (" + entity.rect.toString() + ")]. SDL Error: " + SDL_GetError(), Debug::error);
			else
				return true;
		}

		/* If nothing was rendered so far, simply render the rect */
		DrawRect(entity.rect.color, entity.rect);

		return true;
	}
}
