#pragma once

#ifdef LIB_SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#elif LIB_GLFW
#include "glad/gl.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#endif

#include "Circle.hpp"
#include "Color.hpp"
#include "Utils.hpp"
#include "Entity.hpp"
#include "Polygon.hpp"

namespace Birb
{
	class Window
	{
	public:
		Window(); ///< Initializes a window without any parameters. Shouldn't be used
		~Window();
		Window(const std::string& p_title, const Vector2int& p_window_dimensions, const int& p_refresh_rate, const bool& resizable); ///< Creates a window and initializes SDL2 stuff and a renderer

		/* -- Init stuff functions -- */
#ifdef LIB_SDL
		static void InitSDL(); ///< Initializes SDL2 (if its not already initialized)
		static void InitSDL_image(); ///< Initializes SDL2_image (if its not already initialized)
#endif /* LIB_SDL */
		/* -------------------------- */

		/* -- Rendering and cleanup functions -- */
		void Clear(); ///< Clear the renderer so new stuff can be rendered to it without old stuff staying
		void Display(); ///< Displays the renderer. Should be run after everything has been drawn to the renderer
		/* ------------------------------------- */

		/* -- Cursor functions -- */
		Vector2int CursorPosition() const; ///< Returns the current cursor position relative to the window
		bool CursorInRect(const Rect& rect) const; ///< Checks if the cursor is inside of the given rect dimensions
		/* ---------------------- */

		/* -- Basic window events -- */
		void SetWindowSize(const Vector2int& dimensions);
		bool PollEvents(); ///< Runs SDL_PollEvent and saves the result to the *event* variable
#ifdef LIB_SDL
		void EventTick(const SDL_Event& event, bool* GameRunning);
		SDL_Event event;
#elif LIB_GLFW
		void EventTick(bool* GameRunning);
#endif
		/* ------------------------- */

		/* -- Window variables -- */
		std::string win_title; ///< Window title text
		int refresh_rate; ///< Window refreshrate. Can be changed during runtime if needed for some reason
#ifdef LIB_SDL
		SDL_Window* 	win;
		SDL_Renderer* 	renderer;
#elif LIB_GLFW
		GLFWwindow* 	glWindow;
		int 			frameBufferWidth;
		int 			frameBufferHeight;
#endif

		Vector2int dimensions; ///< Current window dimensions
		Vector2int original_window_dimensions; ///< Window dimensions on application startup before its modified by the user
		Vector2f window_dimensions_multiplier(); ///< Returns the difference between the current and original window dimensions.
		/* ---------------------- */

	private:
		void Cleanup(); ///< Frees resources allocated for the window and deinitializes SDL2 things

#ifdef LIB_SDL
		/* SDL Functions */
		void bSDL_InitWindow(const bool& resizable);
#elif LIB_GLFW
		/* GLFW Functions */
		void bGLFW_InitWindow(const bool& resizable);
#endif

	};
}
