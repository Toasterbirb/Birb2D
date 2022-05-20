#ifdef LIB_SDL
#include "SDL/SDLwindow.hpp"
#include "Diagnostics.hpp"
#include "Logger.hpp"
#include "Values.hpp"

namespace SDL
{
	Window::Window(const std::string& title, const Birb::Vector2int& window_dimensions, SDL_Window* win, SDL_Renderer* renderer, const int& refresh_rate, const bool& resizable)
	{
#ifdef DEBUG
		Birb::Debug::Log("Creating window '" + title + "'...");
#endif

		/* Create a new window and initialize stuff for it */
		InitSDL();
		InitSDL_image();

		if (resizable)
			win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_dimensions.x, window_dimensions.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		else
			win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_dimensions.x, window_dimensions.y, SDL_WINDOW_SHOWN);

		if (win == NULL)
		{
			Birb::Debug::Log("Window failed to init: " + (std::string)SDL_GetError(), Birb::Debug::error);
			exit(1);
		}

		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			Birb::Debug::Log("Renderer failed to init: " + (std::string)SDL_GetError(), Birb::Debug::error);
			exit(1);
		}

		/* Set some global rendering variables */
		Birb::Global::RenderVars::MainWindow 	= win;
		Birb::Global::RenderVars::Renderer 		= renderer;

		Birb::Global::RenderVars::RefreshRate = refresh_rate;

#ifdef DEBUG
		Birb::Debug::Log("Window '" + title + "' created successfully!");
#endif
	}

	void Window::InitSDL()
	{
		/* Check if SDL has already been initialized */
		if (Birb::Global::IsInit::SDL)
			return;

#ifdef DEBUG
		if (Birb::Diagnostics::Debugging::InitMessages)
			Birb::Debug::Log("Initializing SDL...");
#endif

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) > 0)
		{
			Birb::Debug::Log("SDL Init failed: " + (std::string)SDL_GetError(), Birb::Debug::error);
			exit(2);
		}
		else
		{
			Birb::Global::IsInit::SDL = true;
		}
	}

	void Window::InitSDL_image()
	{
		/* Check if SDL_image has already been initialized */
		if (Birb::Global::IsInit::SDL_image)
			return;

#ifdef DEBUG
		if (Birb::Diagnostics::Debugging::InitMessages)
			Birb::Debug::Log("Initializing SDL_image...");
#endif

		if (!(IMG_Init(IMG_INIT_PNG)))
		{
			Birb::Debug::Log("IMG_Init has failed" + (std::string)SDL_GetError(), Birb::Debug::error);
			exit(2);
		}
		else
		{
			Birb::Global::IsInit::SDL_image = true;
		}
	}
}
#endif /* LIB_SDL */
