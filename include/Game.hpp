#pragma once

#include "DebugMenu.hpp"
#include "ErrorFuse.hpp"
#ifndef DISTCC
#include "STD.hpp"
#else
#include <functional>
#endif

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer.h"

#include "ResourceMonitor.hpp"
#include "Timestep.hpp"
#include "Vector/Vector2Int.hpp"

namespace Birb
{
	class Window;

	class Game : public ErrorFuse
	{
	public:
		/// Game window settings
		struct WindowOpts
		{
			std::string title = "Birb2D game";
			Vector2Int window_dimensions = Vector2Int(1280, 720);
			int refresh_rate = 75;
			bool resizable = false;
		};

		Game(WindowOpts window_options,
				std::function<void(Game& game)> start_func,
				std::function<void(Game& game)> input_func,
				std::function<void(Game& game)> update_func,
				std::function<void(Game& game)> render_func);

		/// When this variable is set to false, the game loop
		/// will quit at the start of the next frame
		bool application_running;

		/// Start calling the game loop functions
		void Start();

		/* Game functions. The functions will be called
		 * in the same order as they are listed down below */

		/// start() is called only called once. It should be used
		/// for constructing anything needed in the game loop
		/// instead of bloating the main() function
		std::function<void(Game& game)> start;

		/// Handles any user input, like keyboard, mouse etc.
		std::function<void(Game& game)> input;

		/// This function is meant for handling any game logic
		/// before rendering
		std::function<void(Game& game)> update;

		/// Same as update(), but gets run with a fixed framerate.
		/// By default it is 25fps, but it can be controller via
		/// a variable in TimeStep.
		///
		/// FixedUpdate() gets run on a separate thread similar to post_render,
		/// so it shouldn't be used with anything related to SDL that can't be
		/// multithreaded
		std::function<void()> fixed_update;

		/// Anything to do with rendering happens in here
		std::function<void(Game& game)> render;

		/// This function gets ran on a separate thread after
		/// the frame has been rendered and the main thread is
		/// waiting to keep up with the refreshrate. You can use
		/// that downtime for preparing things for the next frame
		/// or do some cleanup.
		std::function<void()> post_render;

		/// A cleanup function to free any heap allocations etc.
		/// It gets ran after the game loop has finished and the
		/// application would be closed
		std::function<void()> cleanup;

		/// Game window that the game loop class creates
		Window* window;

		/// A shortcut to the event variable in the window variable
		SDL_Event* event;

		/// ImGui menu for holding different runtime editor-like
		/// tools
		DebugMenu debug_menu;

		TimeStep* time_step();

	private:
		void WindowDisplay(Window& game_window);

		/* Placeholder functions for optional game loop functions */
		static void fixed_update_placeholder();
		static void post_render_placeholder();
		static void cleanup_placeholder();

		TimeStep timeStep;
		WindowOpts window_options;

		Diagnostics::ResourceMonitor statistics;

		ImGuiIO* imgui_io;
	};
}
