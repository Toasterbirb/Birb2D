#pragma once

#include "SDL.hpp"

#ifdef DISTCC
#include <functional>
#else
#include "STD.hpp"
#endif

#include "Circle.hpp"
#include "Color.hpp"
#include "Input.hpp"
#include "Utils.hpp"
#include "Polygon.hpp"
#include "Render.hpp"

namespace Birb
{
	class Window
	{
	public:
		Window(); ///< Initializes a window without any parameters. Shouldn't be used
		~Window();
		Window(const std::string& title, const Vector2Int& window_dimensions, int refresh_rate, bool resizable); ///< Creates a window and initializes SDL2 stuff and a renderer

		/* -- Init stuff functions -- */
		static void InitSDL(); ///< Initializes SDL2 (if its not already initialized)
		static void InitSDL_image(); ///< Initializes SDL2_image (if its not already initialized)
		/* -------------------------- */

		/* -- Rendering and cleanup functions -- */
		void Clear(); ///< Clear the renderer so new stuff can be rendered to it without old stuff staying
		void Display(); ///< Displays the renderer. Should be run after everything has been drawn to the renderer
		/* ------------------------------------- */

		/* -- Cursor functions -- */
		Vector2Int CursorPosition() const; ///< Returns the current cursor position relative to the window
		bool CursorInRect(const Rect& rect) const; ///< Checks if the cursor is inside of the given rect dimensions
		/* ---------------------- */

		/* -- Basic window events -- */
		void SetWindowSize(const Vector2Int& dimensions);
		bool PollEvents(); ///< Runs SDL_PollEvent and saves the result to the *event* variable
		void EventTick(const SDL_Event& event, bool* GameRunning);
		SDL_Event event;
		Input::KeyCode key_event() const;
		bool isKeyDown() const;
		bool isKeyUp() const;
		bool isMouseDown() const;
		bool isMouseUp() const;
		/* ------------------------- */

		/* -- Window event callbacks -- */
		std::function<void(Window& window)> OnWindowResize;
		/* ---------------------------- */

		/* -- Window variables -- */
		std::string win_title; ///< Window title text
		int refresh_rate; ///< Window refreshrate. Can be changed during runtime if needed for some reason
		SDL_Window* win;
		SDL_Renderer* renderer;
		Vector2Int dimensions; ///< Current window dimensions
		Vector2Int original_window_dimensions; ///< Window dimensions on application startup before its modified by the user
		Vector2 window_dimensions_multiplier(); ///< Returns the difference between the current and original window dimensions.
		/* ---------------------- */

	private:
		static void DefaultOnWindowResize(Window& window);
		void Cleanup(); ///< Frees resources allocated for the window and deinitializes SDL2 things
	};
}
