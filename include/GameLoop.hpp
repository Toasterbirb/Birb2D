#pragma once
#include "STD.hpp"
#include "Timestep.hpp"
#include <thread>

namespace Birb
{
	class Window;

	class GameLoop
	{
	public:
		GameLoop(Window& main_window,
				std::function<void()> start_func,
				std::function<void(const SDL_Event& input_event)> input,
				std::function<void(const TimeStep& ts)> update_func,
				std::function<void()> render);

		/// When this variable is set to false, the game loop
		/// will quit at the start of the next frame
		bool application_running;

		/// Start calling the game loop functions
		void StartLoop();

		/* Gameloop functions. The functions will be called
		 * in the same order as they are listed down below */

		/// start() is called only called once. It should be used
		/// for constructing anything needed in the game loop
		/// instead of bloating the main() function
		std::function<void()> start;

		/// Handles any user input, like keyboard, mouse etc.
		std::function<void(const SDL_Event& input_event)> input;

		/// This function is meant for handling any game logic
		/// before rendering
		std::function<void(const TimeStep& ts)> update;

		/// Anything to do with rendering happens in here
		std::function<void()> render;

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

	private:
		/* Placeholder functions for optional gameloop functions */
		static void post_render_placeholder();
		static void cleanup_placeholder();

		TimeStep timeStep;
		Window& window;
	};
}
