#pragma once

#include "Entities/Image.hpp"
#include "Entities/ProgressBar.hpp"
#include "Entities/Text.hpp"
#include "ErrorFuse.hpp"
#include <vector>
#ifndef DISTCC
#include "STD.hpp"
#else
#include <functional>
#endif

#include "Audio.hpp"
#include "Input.hpp"
#include "MainMenuSettings.hpp"
#include "Scene.hpp"

namespace Birb
{
	class Game;

	/// Template main menu for simple needs. Useful for
	/// game jams etc. where there might not be enough time
	/// to create a fully polished main menu but the game
	/// still needs some options menu and an exit button
	class MainMenu : public ErrorFuse
	{
	public:
		MainMenu();
		MainMenu(Game& game, MainMenuSettings& settings);
		void Launch();

	private:
		Game* game;
		MainMenuSettings* settings;

		Scene menu_scene;
		Scene credits_scene;
		Entity::Text title_text;
		Rect background;

		Entity::Text window_title_text;

		/* Settings panel */
		Scene settings_scene;

		struct Setting
		{
			enum SettingType
			{
				TOGGLE, SLIDER
			};

			Setting();
			Setting(const Vector2Int& pos, const std::string& text, SettingType type, MainMenuSettings& settings);
			void AddToScene(Scene* scene);

			Vector2Int position;
			Entity::Text text;
			Entity::ProgressBar button;
		};

		Setting volume_slider;
		Audio::SoundFile volume_slider_sound;
		Audio::SoundFile button_hover;

		/* Credits panel */
		Entity::Text credits_text;


		std::vector<Entity::Text> menu_buttons;

		void StartGame();
	};
}
