#pragma once
#include "STD.hpp"
#include "Timestep.hpp"
#include "Vector/Vector2Int.hpp"

namespace Birb
{
	class Window;

	class Game
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

		TimeStep* time_step();

	private:
		/* Placeholder functions for optional game loop functions */
		static void post_render_placeholder();
		static void cleanup_placeholder();

		TimeStep timeStep;
		WindowOpts window_options;

#ifndef __WINDOWS__
		std::future<void> post_render_future;
#endif
	};
}
