#include <iostream>
#include <SDL2/SDL.h>
#include "Entity.hpp"
#include "Logger.hpp"
#include "Values.hpp"
#include "Timestep.hpp"
#include "Renderwindow.hpp"

/* Variables */
bool GameRunning = true;

int main(int argc, char **argv)
{
	Debug::Log("Starting Pong!");
	Debug::Log("Working directory: " + (std::string)argv[0]);
	std::string workdir = (std::string)argv[0];

	size_t pos = std::string::npos;

	// Search for the substring in string in a loop untill nothing is found
	while ((pos  = workdir.find("/pong") )!= std::string::npos)
	{
		// If found then erase it from string
		workdir.erase(pos, std::string("/pong").length());
	}

	Birb2D::Window window("Pong", Vector2int(1280, 720), 240);
	Birb2D::TimeStep timeStep;

	/* Initialize timestep */
	timeStep.Init();

	/* Gameloop variables */
	SDL_Event event;
	TTF_Font* titleFont = Birb2D::Resources::LoadFont(workdir + "/res/fonts/manaspace/manaspc.ttf", 16);
	Birb2D::Entity title("Title", Vector2int(0, 0), Birb2D::TextComponent("Ping Pong", titleFont, &Colors::White));
	title.localScale = { 2.2, 2.2 };
	Birb2D::Entity testPicture("Gigachad", Vector2int(150, 150), Birb2D::Resources::LoadTexture(workdir + "/res/textures/giga_stretch.png"));
	testPicture.localScale = { 0.5, 0.5 };

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
		Birb2D::Render::DrawEntity(title);
		Birb2D::Render::DrawRect(Colors::White, Rect(25, 40, 300, 300));
		Birb2D::Render::DrawCircle(Colors::Red, Vector2int(250, 260), 150);
		Birb2D::Render::DrawCircle(Colors::Green, Vector2int(290, 260), 150);
		Birb2D::Render::DrawEntity(testPicture);
		Birb2D::Render::DrawCircle(Colors::Blue, Vector2int(190, 360), 150);
		window.Display();
		/* End of rendering */
	}

	Debug::Log("Starting cleanup...");
	window.Cleanup();
	SDL_Quit();
	Debug::Log("Game should be closed now!");
	return 0;
}
