#include "../include/Audio.hpp"
#include "../include/Editor.hpp"
#include "../include/RenderWindow.hpp"
#include "../include/Widgets.hpp"
#include "../include/Entity.hpp"

#include <iostream>
#include <vector>


int main(int argc, char* argv[])
{
	RenderWindow window("Birb2D Editor", 1280, 720, 60);

	// ### Editor loop ###
	std::vector<Entity> entities = {};
	
	// Widgets
	Font baseFont("../res/fonts/manaspace/manaspc.ttf", Widget::Colors::Black, 16);
	Widget::TopBar topbar(window, 32, Widget::Colors::Black, baseFont);
	Entity testText("Test text", "testing...", Vector2f(10, 10), baseFont);

	Texture texture;
	texture.sdlTexture = window.loadTexture("../res/textures/giga_stretch.png");
	Entity testPicture("Test texture", Vector2f(0, 32), 0.4, Vector2f(1280, 720), texture);

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
						std::cout << "Quit event!" << std::endl;
						editorRunning = false;
						break;

					case (SDL_WINDOWEVENT):
						if (event.window.event == SDL_WINDOWEVENT_RESIZED)
						{
							window.SetWindowSize(event.window.data1, event.window.data2);
						}
						break;

					default:
						break;
				}

				//if (event.type == SDL_QUIT)
				//{
				//}
			}

			window.timestepStep();
		}
		window.timestepEnd();

		// ### Render stuff ###
		window.clear();
		topbar.refresh(window.getDimensions());
		window.render(testPicture);

		window.display();
		// ####################
	}

	// ### End of editor loop ###

	// Stop audio
	Mix_CloseAudio();
	Mix_Quit();

	window.QuitSDL();
	return 0;
}
