#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <functional>
#endif

namespace Birb
{
	class Game;

	/// Template main menu for simple needs. Useful for
	/// game jams etc. where there might not be enough time
	/// to create a fully polished main menu but the game
	/// still needs some options menu and an exit button
	class MainMenu
	{
	public:
		MainMenu(Game& game);
		void Launch();

	private:
		Game& game;
		std::function<void(Game& game)> game_input;
		std::function<void(Game& game)> game_update;
		std::function<void(Game& game)> game_render;

		static void menu_input(Game& game);
		static void menu_update(Game& game);
		static void menu_render(Game& game);

		void StartGame();
	};
}
