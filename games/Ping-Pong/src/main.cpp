#include <iostream>
#include <SDL2/SDL.h>
#include "Logger.hpp"
#include "Renderwindow.hpp"
#include "Timestep.hpp"

/* Variables */
bool GameRunning = true;

int main(int argc, char **argv)
{
	Debug::Log("Starting Pong!");
	Debug::Log("Working directory: " + (std::string)argv[0]);

	Birb2D::Window window("Pong", Vector2int(1280, 720), 240);
	Birb2D::TimeStep timeStep;

	/* Initialize timestep */
	timeStep.Init();

	/* Gameloop variables */
	SDL_Event event;

	while (GameRunning)
	{
		timeStep.Start();
		while (timeStep.Running())
		{
			while (SDL_PollEvent(&event) != 0)
			{
				window.EventTick(event, &GameRunning);
			}

			timeStep.Step();
		}

		timeStep.End();

		/* Render stuff */
		window.Clear();
		window.Display();
		/* End of rendering */
	}

	Debug::Log("Starting cleanup...");
	window.Cleanup();
	SDL_Quit();
	Debug::Log("Game should be closed now!");
	return 0;
}
