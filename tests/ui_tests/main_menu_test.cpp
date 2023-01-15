#include "Entities/Text.hpp"
#include "Font.hpp"
#include "Scene.hpp"
#include "Vector/Vector2Int.hpp"
#include "doctest.h"
#include "Game.hpp"
#include "MainMenu.hpp"
#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace Birb;

namespace BirbTest
{
	void menu_start(Game& game);
	void menu_input(Game& game);
	void menu_update(Game& game);
	void menu_render(Game& game);
	void menu_post_render();
	void menu_cleanup();

	Font* font;

	Entity::Text game_reached_text;
	Scene game_scene;


	TEST_CASE("Rendering: Main menu")
	{
		Game::WindowOpts win_opts;
		win_opts.title = "Main menu test";
		Game game(win_opts, menu_start, menu_input, menu_update, menu_render);
		game.cleanup = menu_cleanup;
		game.Start();
	}

	void menu_start(Game& game)
	{
		font = new Font("fonts/freefont/FreeMonoBold.ttf", 64);

		game_reached_text = Entity::Text("Game reached", Vector2Int(128, 128), "This is the game", *font, Colors::Nord::Frost::nord9);
		game_reached_text.renderingPriority = 1;
		game_scene.AddObject(&game_reached_text);

		/* Create the main menu and start it */
		MainMenuSettings menu_settings;
		MainMenu main_menu(game, menu_settings);
		main_menu.Launch();
	}

	void menu_input(Game& game)
	{

	}

	void menu_update(Game& game)
	{

	}

	void menu_render(Game& game)
	{
		game_scene.Render();
	}

	void menu_post_render()
	{

	}

	void menu_cleanup()
	{
		delete font;
	}
}
