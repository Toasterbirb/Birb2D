#pragma once

#include "SDL.hpp"

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
		static void InitSDL(); ///< Initializes SDL2 (if its not already initialized)
		static void InitSDL_image(); ///< Initializes SDL2_image (if its not already initialized)
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
		void EventTick(const SDL_Event& event, bool* GameRunning);
		SDL_Event event;
		/* ------------------------- */

		/* -- Window variables -- */
		std::string win_title; ///< Window title text
		int refresh_rate; ///< Window refreshrate. Can be changed during runtime if needed for some reason
		SDL_Window* win;
		SDL_Renderer* renderer;
		Vector2int dimensions; ///< Current window dimensions
		Vector2int original_window_dimensions; ///< Window dimensions on application startup before its modified by the user
		Vector2f window_dimensions_multiplier(); ///< Returns the difference between the current and original window dimensions.
		/* ---------------------- */

	private:
		void Cleanup(); ///< Frees resources allocated for the window and deinitializes SDL2 things
	};

	/// Methods for rendering things
	namespace Render
	{
		bool DrawEntity(Entity& entity); ///< Renders an entity

		void ResetDrawColor(); ///< Resets the drawing color back to black, so that the window background color stays the same
		void SetRenderDrawColor(const Color& color); ///< Sets the drawing color for base SDL2 drawing functions

		void DrawRect(const Color& color, const Rect& dimensions); ///< Draw filled rect
		void DrawRect(const Color& color, const Rect& dimensions, const int& width); ///< Draw hollow rect

		void DrawLine(const Color& color, const Vector2int& pointA, const Vector2int& pointB); ///< Draw a line between points A and B
		void DrawLine(const Color& color, const Vector2f& pointA, const Vector2f& pointB); ///< Draw a line between points A and B
		void DrawLine(const Line& line); ///< Draw a line between points A and B
		void DrawLine(const Line& line, const int& thickness); ///< Draw a thick line between points A and B

		void DrawLines(const Color& color, Vector2int* points, const int& pointCount); ///< Draw lines between multiple points at once
		void DrawLines(const Color& color, Vector2f* points, const int& pointCount); ///< Draw lines between multiple points at once

		bool DrawCircle(const Circle& circle); ///< Draw a circle around a point
		bool DrawCircle(const Color& color, const Vector2int& pos, const int& radius); ///< Draw a circle around a point

		bool DrawPolygon(const Color& color, Vector2int* points, const int& pointCount); ///< Draw a polygon from multiple points
		bool DrawPolygon(const Color& color, const std::vector<Vector2int>& points); ///< Draw a polygon from multiple points
		bool DrawPolygon(const Color& color, Vector2f* points, const int& pointCount); ///< Draw a polygon from multiple points
		bool DrawPolygon(const Color& color, const std::vector<Vector2f>& points); ///< Draw a polygon from multiple points
		bool DrawPolygon(const Polygon& polygon); ///< Draw a polygon

	};
}
