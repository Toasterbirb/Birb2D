#include "Renderwindow.hpp"
#include "Entities/Animation.hpp"
#include "Entities/ProgressBar.hpp"
#include "Values.hpp"
#include "Logger.hpp"
#include "Diagnostics.hpp"
#include "Physics.hpp"
#include "microprofile.h"

#define PROFILER_GROUP "Rendering"
#define PROFILER_COLOR MP_LIGHTBLUE

namespace Birb
{
	Window::Window()
	{
		InitSDL();
		InitSDL_image();
	}

	Window::Window(const std::string& title, const Vector2Int& window_dimensions, int refresh_rate, bool resizable)
	:win_title(title), refresh_rate(refresh_rate), dimensions(window_dimensions), original_window_dimensions(window_dimensions)
	{

		Debug::Log("Creating window '" + win_title + "'...");

		/* Create a new window and initialize stuff for it */
		InitSDL();
		InitSDL_image();

		if (resizable)
			win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_dimensions.x, window_dimensions.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		else
			win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_dimensions.x, window_dimensions.y, SDL_WINDOW_SHOWN);

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

	Vector2Int Window::CursorPositionWorld() const
	{
		return CursorPosition() + Global::RenderVars::CameraPosition.ToInt();
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
}
