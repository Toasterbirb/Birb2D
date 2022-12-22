#include <functional>
#include "GameLoop.hpp"
#include "Timestep.hpp"

namespace Birb
{
	GameLoop::GameLoop(Window& main_window,
			std::function<void()> start_func,
			std::function<void(const SDL_Event& input_event)> input_func,
			std::function<void(const TimeStep& ts)> update_func,
			std::function<void()> render_func)
	:start(start_func), input(input_func), update(update_func), render(render_func), window(main_window)
	{
		cleanup 	= cleanup_placeholder;
		post_render = post_render_placeholder;
	}

	void GameLoop::StartLoop()
	{
		application_running = true;

		/* Initialize timestep */
		timeStep.Init(&window);

		/* Call the start function before starting the game loop */
		start();

		/* The main game loop */
		while (application_running)
		{
			timeStep.Start();
			while (timeStep.Running())
			{
				/* Poll input */
				while (window.PollEvents())
				{
					window.EventTick(window.event, &application_running);
					input(window.event);
				}

				timeStep.Step();
			}

			/* Handle any game logic */
			update(timeStep);

			/* Handle rendering */
			window.Clear();
			render();
			window.Display();

			/* Start the post render thread */
			std::thread post_render_thread(post_render);

			/* End of timestep */
			timeStep.End();

			/* Join the post render thread */
			post_render_thread.join();
		}

		/* Free memory allocations and stuff. Up to the user to decide */
		cleanup();
	}

	void GameLoop::post_render_placeholder()
	{}

	void GameLoop::cleanup_placeholder()
	{}
}
