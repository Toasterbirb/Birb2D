#include "DebugMenu.hpp"
#include "Diagnostics.hpp"
#include "Game.hpp"
#include "Utils.hpp"
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
		cleanup 		= cleanup_placeholder;
		post_render 	= post_render_placeholder;
		fixed_update 	= fixed_update_placeholder;

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
		event = &window->event;

		/* Initialize timestep */
		timeStep.Init(&game_window);

		/* Initialize ImGui */
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		imgui_io = &ImGui::GetIO(); (void)imgui_io;
		imgui_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui_ImplSDL2_InitForSDLRenderer(window->win, window->renderer);
		ImGui_ImplSDLRenderer_Init(window->renderer);

		/* Initialize statistics */
		statistics = Diagnostics::ResourceMonitor(&timeStep);

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

					if (window->isKeyDown())
					{
						/* Toggle the debug overlay */
						if (event->key.keysym.scancode == SDL_SCANCODE_F8)
							Diagnostics::Debugging::Overlays::Debug = !Diagnostics::Debugging::Overlays::Debug;
					}

					if (Diagnostics::Debugging::Overlays::Debug)
						ImGui_ImplSDL2_ProcessEvent(event);

					input(*this);
				}

				timeStep.Step();
			}

			/* Handle any game logic */
			update(*this);

			/* Handle rendering and ImGui */
			game_window.Clear();
			render(*this);

			if (Diagnostics::Debugging::Overlays::Debug)
			{
				ImGui_ImplSDLRenderer_NewFrame();
				ImGui_ImplSDL2_NewFrame();
				ImGui::NewFrame();

				DebugMenu::ResouceMonitor(statistics, timeStep);
				debug_menu.EntityMenu();

				ImGui::Render();
				SDL_RenderSetScale(window->renderer, imgui_io->DisplayFramebufferScale.x, imgui_io->DisplayFramebufferScale.y);
				ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
			}

			WindowDisplay(game_window);

			/* End of timestep */
			timeStep.End();

		}

		/* Free memory allocations and stuff. Up to the user to decide */
		debug_menu.Clear();
		statistics.Free();
		cleanup();

		/* Stop ImGui */
		ImGui_ImplSDLRenderer_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

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

		/* Check fuses */
		if (statistics.ErrorFuseStatus())
			BlowErrorFuse();
	}

	TimeStep* Game::time_step()
	{
		return &timeStep;
	}

	void Game::WindowDisplay(Window& game_window)
	{
		/* mingw doesn't really like std::future yet,
		 * so we'll have to skip on multithreading on
		 * Windows for now :( */
		if (timeStep.ShouldRunFixedUpdate())
		{
			fixed_update();

			if (Diagnostics::Debugging::Overlays::Debug)
				statistics.Refresh();
		}

		/* Render the statistics overlay if debugging is enabled */
		//if (Diagnostics::Debugging::Overlays::ResourceMonitor)
		//	statistics.Render();

		game_window.Display();

		post_render();
	}

	void Game::fixed_update_placeholder()
	{}

	void Game::post_render_placeholder()
	{}

	void Game::cleanup_placeholder()
	{}
}
