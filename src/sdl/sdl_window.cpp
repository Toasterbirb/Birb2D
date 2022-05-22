#ifdef LIB_SDL
#include "Window.hpp"
#include "Logger.hpp"

namespace Birb
{
	void Window::bSDL_InitWindow(const bool& resizable)
	{
		/* ------------------------- */
		/* SDL Window implementation */
		/* ------------------------- */

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
	}
}
#endif

