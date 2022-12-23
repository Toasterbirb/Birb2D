#include "Game.hpp"

namespace Birb
{
	Game::Game(WindowOpts window_options,
			std::function<void()> start_func,
			std::function<void(const SDL_Event& input_event)> input_func,
			std::function<void(const TimeStep& ts)> update_func,
			std::function<void()> render_func)
	:start(start_func), input(input_func), update(update_func), render(render_func), window_options(window_options)
	{
		cleanup 	= cleanup_placeholder;
		post_render = post_render_placeholder;
	}

	void Game::Start()
	{
		application_running = true;

		/* Create the game window */
		Window game_window(window_options.title,
				window_options.window_dimensions,
				window_options.refresh_rate,
				window_options.resizable);
		window = &game_window;

		/* Initialize timestep */
		timeStep.Init(&game_window);

		/* Call the start function before starting the game loop */
		start();

		/* The main game loop */
		while (application_running)
		{
			timeStep.Start();
			while (timeStep.Running())
			{
				/* Poll input */
				while (window->PollEvents())
				{
					window->EventTick(window->event, &application_running);
					input(window->event);
				}

				timeStep.Step();
			}

			/* Handle any game logic */
			update(timeStep);

			/* Handle rendering */
			game_window.Clear();
			render();
#ifndef __WINDOWS__
			/* Start the post render thread */
			post_render_future = std::async(post_render);
#endif
			game_window.Display();

#ifdef __WINDOWS__
			/* mingw doesn't really like std::future yet,
			 * so we'll have to skip on multithreading on
			 * Windows for now :( */
			post_render();
#endif

			/* End of timestep */
			timeStep.End();

#ifndef __WINDOWS__
			/* Join the post render thread */
			post_render_future.wait();
#endif
		}

		/* Free memory allocations and stuff. Up to the user to decide */
		cleanup();
	}

	TimeStep* Game::time_step()
	{
		return &timeStep;
	}

	void Game::post_render_placeholder()
	{}

	void Game::cleanup_placeholder()
	{}
}