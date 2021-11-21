#include "../include/Audio.hpp"
#include "../include/Editor.hpp"
#include "../include/RenderWindow.hpp"
#include "../include/Widgets.hpp"
#include "../include/Entity.hpp"
#include "../include/Values.hpp"
#include "../include/Logger.hpp"

#include <iostream>
#include <vector>

void Entry();

#ifndef PLATFORM_WIN
int main(int argc, char* argv[])
{
	Entry();
	return 0;
}
#else
int WinMain(int argc, char* argv[])
{
	Entry();
	return 0;
}
#endif

void Entry()
{
	Debug::Log("Engine starpoint");
	int refreshRate = 240;
	Birb2D::RenderWindow window("Birb2D Editor", 1280, 720, refreshRate);

	// ### Editor loop ###
	std::vector<Birb2D::Entity> entities = {};
	
	// Widgets
	Birb2D::Font baseFont("../res/fonts/manaspace/manaspc.ttf", Colors::Black, 16);
	Birb2D::Font buttonFont("../res/fonts/freefont/FreeMono.ttf", Colors::Black, 12);
	Birb2D::Widgets::TopBar topbar(window, 32, Colors::Black, baseFont);
	
	std::vector<Birb2D::Widgets::Widget> buttons;
	Birb2D::Widgets::Widget testButton(window, Birb2D::Widgets::Button, Rect(50, 50, 120, 30), Colors::Green, "A button", Rect(5, 5, 96, 24), buttonFont);
	buttons.push_back(testButton);

	Birb2D::Texture texture;
	texture.sdlTexture = window.loadTexture("../res/textures/giga_stretch.png");
	Birb2D::Entity testPicture("Test texture", Vector2f(0, 32), 0.4, Vector2f(1280, 720), texture);

	SDL_Event event;
	bool editorRunning = true;
	while (editorRunning)
	{
		window.timestepStart();
		while (window.timestepRunning())
		{
			while (SDL_PollEvent(&event) != 0)
			{
				switch (event.type)
				{
					case (SDL_QUIT):
						Debug::Log("Quit event");
						editorRunning = false;
						break;

					case (SDL_WINDOWEVENT):
						if (event.window.event == SDL_WINDOWEVENT_RESIZED)
						{
							window.SetWindowSize(event.window.data1, event.window.data2);
						}
						break;

					case (SDL_MOUSEBUTTONDOWN):
						for (int i = 0; i < (int)buttons.size(); i++)
						{
							buttons[i].refresh(Birb2D::Widgets::RefreshAction::Click);
						}
						break;

					default:
						break;
				}

			}

			window.timestepStep();
		}
		window.timestepEnd();

		// ###### Render stuff ######
		window.clear();
		topbar.refresh(window.getDimensions());
		window.render(testPicture);
		testButton.refresh(Birb2D::Widgets::RefreshAction::Render);

		window.display();
		// ##########################
	}

	// ### End of editor loop ###

	// Stop audio
	Mix_CloseAudio();
	Mix_Quit();

	window.QuitSDL();
}
