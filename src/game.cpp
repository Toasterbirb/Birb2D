#include "Game.hpp"
#include "Values.hpp"

namespace Birb
{
	Game::Game(WindowOpts window_options,
			std::function<void(Game& game)> start_func,
			std::function<void(Game& game)> input_func,
			std::function<void(Game& game)> update_func,
			std::function<void(Game& game)> render_func)
	:start(start_func), input(input_func), update(update_func), render(render_func), window_options(window_options)
	{
		cleanup 	= cleanup_placeholder;
		post_render = post_render_placeholder;

		/* Initialize SDL stuff */
		if (TTF_Init() == -1)
		{
			Debug::Log("TTF_Init has failed: " + static_cast<std::string>(TTF_GetError()), Debug::error);
			exit(2);
		}
		else
		{
			Global::IsInit::SDL_ttf = true;
		}
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


		/* Initialize statistics */
		statistics = new Diagnostics::Statistics(&timeStep);

		/* Call the start function before starting the game loop */
		start(*this);

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
					input(*this);
				}

				timeStep.Step();
			}

			/* Handle any game logic */
			update(*this);

			/* Handle rendering */
			game_window.Clear();
			render(*this);


#ifndef __WINDOWS__
			/* Start the fixed update thread and refresh statistics */
			if (timeStep.ShouldRunFixedUpdate())
			{
				fixed_update_future = std::async(std::launch::async, fixed_update);


				statistics->Refresh();
			}

			/* Render the statistics overlay if debugging is enabled */

			statistics->Render();

			/* Start the post render thread */
			post_render_future = std::async(std::launch::async, post_render);
#endif /* __WINDOWS__ */
			game_window.Display();

#ifdef __WINDOWS__
			/* mingw doesn't really like std::future yet,
			 * so we'll have to skip on multithreading on
			 * Windows for now :( */
			if (timeStep.ShouldRunFixedUpdate())
			{
				fixed_update();


				statistics.Refresh();
			}

			post_render();
#endif /* __WINDOWS__ */

#ifndef __WINDOWS__
			/* Join the fixed update thread */
			fixed_update_future.wait();

			/* Join the post render thread */
			post_render_future.wait();
#endif

			/* End of timestep */
			timeStep.End();

		}

		/* Free memory allocations and stuff. Up to the user to decide */

		statistics->Free();
		delete statistics;
		cleanup();

		/* Quit SDL things */

		/* De-initialize SDL TTF if any fonts have been used */
		if (Global::IsInit::SDL_ttf)
		{
			TTF_Quit();
			Global::IsInit::SDL_ttf = false;
		}

		/* De-initialize SDL_Mixer if audio has been used */
		if (Global::IsInit::SDL_mixer)
		{
			Mix_Quit();
			Global::IsInit::SDL_mixer = false;
		}

		/* Clear the SDL error buffer since it can be a bit leaky */
		SDL_TLSCleanup();
	}

	TimeStep* Game::time_step()
	{
		return &timeStep;
	}

	void Game::fixed_update_placeholder()
	{}

	void Game::post_render_placeholder()
	{}

	void Game::cleanup_placeholder()
	{}
}
