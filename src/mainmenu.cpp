#include "MainMenu.hpp"
#include "Game.hpp"

namespace Birb
{
	MainMenu::MainMenu(Game& game)
	:game(game)
	{
		/* Store the game functions */
		game_input 	= game.input;
		game_update = game.update;
		game_render = game.render;
	}

	void MainMenu::Launch()
	{
		/* Switch the game loop functions to the main menu ones */
		game.input 	= menu_input;
		game.update = menu_update;
		game.render = menu_render;
	}

	void MainMenu::menu_input(Game& game)
	{

	}

	void MainMenu::menu_update(Game& game)
	{

	}

	void MainMenu::menu_render(Game& game)
	{

	}

	void MainMenu::StartGame()
	{
		/* Switch back to the game functions */
	}
}
