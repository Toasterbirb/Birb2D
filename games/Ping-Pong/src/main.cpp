#include <vector>
#include "../../../include/Birb2D.hpp"

void StartGame();
void QuitGame();
bool gameRunning = true;
Birb2D::RenderWindow window("Ping Pong", 1280, 720, 240);
std::vector<Birb2D::Scene*> scenes;
Birb2D::Scene mainMenuScene("Main menu", window, true);
Birb2D::Scene pauseMenuScene("Pause menu", window, false, 2);
Birb2D::Scene gameScene("Game scene", window, false);

int main()
{
	Debug::Log("Starting pinging and ponging");

	// Game loop
	bool holdingKeyDown = false

	// Fonts
	Birb2D::Font titleFont("../res/fonts/freefont/FreeMono.ttf", Colors::White, 64);
	Birb2D::Font mainMenuButtonFont("../res/fonts/freefont/FreeMonoBold.ttf", Colors::White, 32);

	// Entities
	/* Main menu */
	Birb2D::Widgets::Text title(window, Vector2f(50, 50), "Ping Pong", titleFont);

	Birb2D::Widgets::Button playButton(window, Rect(50, 128, 150, 40), Colors::LightGray, "Play", mainMenuButtonFont, StartGame);
	Birb2D::Widgets::Button quitButton(window, Rect(50, 200, 150, 40), Colors::LightGray, "Quit", mainMenuButtonFont, QuitGame);
	mainMenuScene.AddButton({playButton, quitButton});
	mainMenuScene.AddText(title);

	/* Pause menu */
	Birb2D::Widgets::Rectangle pauseMenuBackground(window, Rect(300, 200, 210, 350), Colors::White);
	Birb2D::Widgets::Button pauseQuitButton(window, Rect(310, 210, 190, 40), Colors::LightGray, "Quit", mainMenuButtonFont, QuitGame, 1);
	pauseMenuScene.AddRectangle(pauseMenuBackground);
	pauseMenuScene.AddButton(pauseQuitButton);

	/* Game view */
	Birb2D::Widgets::Text scoreText(window, Vector2f(50, 50), "Score: 0 - 0", titleFont);
	gameScene.AddText(scoreText);

	// Add scenes to a list
	scenes.push_back(&mainMenuScene);
	scenes.push_back(&pauseMenuScene);
	scenes.push_back(&gameScene);
	

	SDL_Event event;
	while (gameRunning)
	{
		window.timestepStart();
		while (window.timestepRunning())
		{
			while (SDL_PollEvent(&event) != 0)
			{
				window.handleBasicWindowEvents(event, &gameRunning);
				for (int i = 0; i < scenes.size(); i++)
					scenes[i]->PollButtonEvents(event);

				switch (event.type)
				{
					// Handle window resizing
					case (SDL_WINDOWEVENT):
						if (event.window.event == SDL_WINDOWEVENT_RESIZED)
							window.SetWindowSize(event.window.data1, event.window.data2);
						break;

					default:
						break;
				}

				// Keyboard input
				if (event.type == SDL_KEYDOWN && !holdingKeyDown)
				{
					holdingKeyDown = true;

					switch (event.key.keysym.sym)
					{
						case (SDLK_ESCAPE):
							if (gameScene.isEnabled())
								pauseMenuScene.toggle();
							break;

						default:
							break;
					}
				}
				else if (event.type == SDL_KEYUP)
				{
					holdingKeyDown = false;
				}
			}

			window.timestepStep();
		}

		window.timestepEnd();

		/* ### Render stuff ### */
		window.clear();

		// Render scenes
		for (int i = 0; i < scenes.size(); i++)
			scenes[i]->Render();

		window.display();
		/* ### End of rendering stuff */
	}

	Debug::Log("Cleanup");
	window.cleanUp();
	Debug::Log("SDL_Quit()");
	SDL_Quit();
	Debug::Log("Game should be closed now");
	return 0;
}

void StartGame()
{
	Debug::Log("Starting the game!");
	mainMenuScene.disable();
	gameScene.enable();
}

void QuitGame()
{
	gameRunning = false;
	Debug::Log("Quiting the game...");
}
