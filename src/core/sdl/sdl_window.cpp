#ifdef LIB_SDL
#include "Window.hpp"
#include "Logger.hpp"
#include "Diagnostics.hpp"

#include <SDL2/SDL_mixer.h>

namespace Birb
{
	Window::Window()
	{
		InitSDL();
		InitSDL_image();
	}

	Window::Window(const std::string& p_title, const Vector2int& p_window_dimensions, const int& p_refresh_rate, const bool& resizable)
	:win_title(p_title), refresh_rate(p_refresh_rate), dimensions(p_window_dimensions), original_window_dimensions(p_window_dimensions), resizable(resizable)
	{
		/* ------------------------- */
		/* SDL Window implementation */
		/* ------------------------- */

		Debug::Log("Creating window '" + win_title + "'...");

		/* Create a new window and initialize stuff for it */
		InitSDL();
		InitSDL_image();

		if (resizable)
			win = SDL_CreateWindow(win_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dimensions.x, dimensions.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		else
			win = SDL_CreateWindow(win_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dimensions.x, dimensions.y, SDL_WINDOW_SHOWN);

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
		Global::RenderVars::RefreshRate = refresh_rate;

		Debug::Log("Window '" + win_title + "' created successfully!");
	}

	void Window::Cleanup()
	{
		Debug::Log("Starting window cleanup for '" + win_title + "'...");

		SDL_DestroyWindow(win);

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

		Debug::Log("Window '" + win_title + "' destroyed!");
	}

	void Window::InitSDL()
	{
		/* Check if SDL has already been initialized */
		if (Global::IsInit::SDL)
			return;

		if (Birb::Diagnostics::Debugging::InitMessages)
			Debug::Log("Initializing SDL...");

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

		if (Birb::Diagnostics::Debugging::InitMessages)
			Debug::Log("Initializing SDL_image...");

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

	void Window::Clear()
	{
		/* Clear the window renderer. Call before rendering stuff */
		SDL_RenderClear(Global::RenderVars::Renderer);
	}

	void Window::Display()
	{
		SDL_RenderPresent(Global::RenderVars::Renderer);
	}

	Vector2int Window::CursorPosition() const
	{
		Vector2int pos;
		SDL_GetMouseState(&pos.x, &pos.y);
		return pos;
	}

	void Window::SetWindowSize(const Vector2int& dimensions)
	{
		SDL_SetWindowSize(win, dimensions.x, dimensions.y);
		this->dimensions = dimensions;
	}

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

	bool Window::PollEvents()
	{
		return (SDL_PollEvent(&event) != 0);
	}
}
#endif

