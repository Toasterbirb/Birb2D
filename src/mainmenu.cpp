#include "Game.hpp"
#include "MainMenu.hpp"
#include "Values.hpp"
#include <iostream>

namespace Birb
{
	MainMenu::MainMenu()
	{

	}

	MainMenu::MainMenu(Game& game, MainMenuSettings& settings)
	:game(&game), settings(&settings)
	{
		Audio::Init(0);

		/* Load the volume slider sound */
		volume_slider_sound = Audio::SoundFile("birb2d_res/sounds/volume_slider.wav");

		/* Load button on-hover sound */
		button_hover = Audio::SoundFile("birb2d_res/sounds/button_hover.wav");

		/* If a background texture is set, use that */
		//if (this->settings->background_texture.isLoaded())
		//{
		//	background = Entity("Main menu background", game.window->dimensions, this->settings->background_texture, -1);
		//}
		//else
		//{
		//	background.rect = Rect(0, 0, this->game->window->dimensions.x, this->game->window->dimensions.y);
		//	background.rect.color = this->settings->background_color;
		//}
		background.color = this->settings->background_color;
		menu_scene.AddObject(&background);

		/* Initialize any entities */
		//title_text = Entity("Title text",
		//		settings.title.position,
		//		EntityComponent::Text(settings.title.text, &this->settings->title.font, &this->settings->title.color),
		//		1);
		title_text = Entity::Text(settings.title.text, this->settings->title.font, this->settings->title.color);
		title_text.rect = this->settings->title.position;
		menu_scene.AddObject(&title_text);

		/* Add button backgrounds to the scene */
		for (size_t i = 0; i < this->settings->buttons.size(); ++i)
			menu_scene.AddObject(&this->settings->buttons[i]->button_background);

		/* Allocate menu buttons */
		menu_buttons = std::vector<Entity::Text>(4);

		for (size_t i = 0; i < menu_buttons.size(); ++i)
		{
			//menu_buttons[i] = Entity("Main menu button text",
			//		Vector2Int(this->settings->buttons[i]->rect.x + this->settings->button_text_padding, this->settings->buttons[i]->rect.y + 7),
			//		EntityComponent::Text(this->settings->buttons[i]->text,
			//			&this->settings->buttons[i]->font,
			//			&this->settings->buttons[i]->text_color),
			//		2);

			menu_buttons[i] = Entity::Text(this->settings->buttons[i]->text,
					Vector2Int(this->settings->buttons[i]->rect.x + this->settings->button_text_padding, this->settings->buttons[i]->rect.y + 7),
					this->settings->buttons[i]->font,
					this->settings->buttons[i]->text_color);
			menu_buttons[i].renderingPriority = 2;

			/* Update button background dimensions to fit the text */
			this->settings->buttons[i]->button_background.w = menu_buttons[i].sprite_dimensions().x + (this->settings->button_text_padding * 2);
			this->settings->buttons[i]->rect = this->settings->buttons[i]->button_background;
		}

		/* Add menu buttons to the scene */
		for (size_t i = 0; i < menu_buttons.size(); ++i)
			menu_scene.AddObject(&menu_buttons[i]);


		/* Construct the settings page */
		settings_scene.Deactivate();
		settings_scene.AddObject(&this->settings->settings_menu.window.background);
		settings_scene.AddObject(&this->settings->settings_menu.window.top_bar);

		//window_title_text = Entity("Settings title text",
		//		Vector2Int(this->settings->settings_menu.window.top_bar.x + 4, this->settings->settings_menu.window.top_bar.y + 4),
		//		EntityComponent::Text("Settings",
		//			&this->settings->settings_menu.window.title_font,
		//			&this->settings->settings_menu.window.title_color),
		//		4);
		window_title_text = Entity::Text("Settings",
				Vector2Int(this->settings->settings_menu.window.top_bar.x + 4, this->settings->settings_menu.window.top_bar.y + 4),
				this->settings->settings_menu.window.title_font,
				this->settings->settings_menu.window.title_color);
		settings_scene.AddObject(&window_title_text);

		/** Create options **/
		int option_padding = 16;
		volume_slider = Setting(Vector2Int(this->settings->settings_menu.window.top_bar.x + option_padding, this->settings->settings_menu.window.top_bar.y + this->settings->settings_menu.window.top_bar.h + option_padding), "Volume ", Setting::SLIDER, settings);
		//volume_slider.button.progressBarComponent.parent_entity = &volume_slider.button;


		/** Construct the credits page **/
		credits_scene.Deactivate();

		//credits_text = Entity("Credits text",
		//		Vector2Int(this->settings->credits_menu.window.top_bar.x + option_padding, this->settings->settings_menu.window.top_bar.y + this->settings->settings_menu.window.top_bar.h + option_padding),
		//		EntityComponent::Text(this->settings->credits_menu.credits_text,
		//			&this->settings->credits_menu.text_font,
		//			&this->settings->credits_menu.window.text_color),
		//		4);
		credits_text = Entity::Text(this->settings->credits_menu.credits_text,
				Vector2Int(this->settings->credits_menu.window.top_bar.x + option_padding, this->settings->settings_menu.window.top_bar.y + this->settings->settings_menu.window.top_bar.h + option_padding),
				this->settings->credits_menu.text_font,
				this->settings->credits_menu.window.text_color);
		credits_text.renderingPriority = 4;
		credits_scene.AddObject(&credits_text);

		/* Scale the credits window to fit the credit text */
		this->settings->credits_menu.window.background.w = credits_text.sprite_dimensions().x + 32;
		this->settings->credits_menu.window.background.h = credits_text.sprite_dimensions().y + this->settings->credits_menu.window.top_bar.h + 32;
		this->settings->credits_menu.window.top_bar.w = this->settings->credits_menu.window.background.w;

		credits_scene.AddObject(&this->settings->credits_menu.window.background);
		credits_scene.AddObject(&this->settings->credits_menu.window.top_bar);
		credits_scene.AddObject(&this->window_title_text);

	}

	void MainMenu::Launch()
	{
		/* Add setting buttons to settings scene */
		volume_slider.AddToScene(&settings_scene);
		settings_scene.SortObjects();

		/* Start a simple game loop for the main menu */
		bool main_menu_running = true;
		bool window_running = true;
		bool mouse_down = false;
		while (main_menu_running)
		{
			game->time_step()->Start();
			while (game->time_step()->Running())
			{
				/* Handle input stuff */
				while (game->window->PollEvents())
				{
					game->window->EventTick(game->window->event, &window_running);

					mouse_down = game->window->isMouseDown();

					/* Handle button hover events */
					for (size_t i = 0; i < settings->buttons.size(); ++i)
					{
						if (game->window->CursorInRect(settings->buttons[i]->rect))
						{
							/* Play a *click* sound on hover */
							if (settings->buttons[i]->button_background.color == settings->buttons[i]->background_color)
								button_hover.play();


							/* Set highlight color */
							settings->buttons[i]->button_background.color = settings->buttons[i]->highlight_color;

							/* Handle button presses */
							if (game->window->isMouseDown())
							{
								switch (i)
								{
									case (MainMenuSettings::PLAY):
									{
										main_menu_running = false;
										break;
									}

									case (MainMenuSettings::SETTINGS):
									{
										window_title_text.SetText("Settings");
										credits_scene.Deactivate();
										settings_scene.Toggle();
										break;
									}

									case (MainMenuSettings::CREDITS):
									{
										window_title_text.SetText("Credits");
										settings_scene.Deactivate();
										credits_scene.Toggle();
										break;
									}

									case (MainMenuSettings::QUIT):
									{
										window_running = false;
										break;
									}
								}
							}
						}
						else
						{
							settings->buttons[i]->button_background.color = settings->buttons[i]->background_color;
						}
					}
				}

				game->time_step()->Step();

				/* If the window was closed manually by the user, pass
				 * the application_running boolean to the game object */
				game->application_running = window_running;

				if (main_menu_running)
					main_menu_running = window_running;

				if (mouse_down)
				{
					float old_volume = volume_slider.button.value;
					volume_slider.button.SetValueFromRelativePoint(game->window->CursorPosition().ToFloat());
					if (!volume_slider_sound.isPlaying() && old_volume != volume_slider.button.value)
					{
						Audio::SetGlobalVolume(volume_slider.button.value);
						volume_slider_sound.play();
					}

				}


				game->window->Clear();
				/* Handle rendering */

				menu_scene.Render();
				settings_scene.Render();
				credits_scene.Render();

				/* End of rendering */
				game->window->Display();

				game->time_step()->End();
			}
		}
	}

	MainMenu::Setting::Setting()
	{}

	MainMenu::Setting::Setting(const Vector2Int& pos, const std::string& text, SettingType type, MainMenuSettings& settings)
	:position(pos)
	{
		//this->text = Entity("Setting option text", pos,
		//		EntityComponent::Text(text,
		//			&settings.settings_menu.setting_font,
		//			&settings.settings_menu.window.text_color),
		//		5);
		this->text = Entity::Text(text, pos, settings.settings_menu.setting_font, settings.settings_menu.window.text_color);
		this->text.renderingPriority = 5;

		switch (type)
		{
			case (SLIDER):
			{
				//this->button = Entity("Setting option button",
				//		Rect(pos.x + this->text.sprite.dimensions().x + 8, pos.y + 2, 128, 16),
				//		3);
				this->button = Entity::ProgressBar(1,
						settings.settings_menu.slider_border_color,
						settings.settings_menu.slider_background_color,
						settings.settings_menu.slider_fill_color);
				this->button.rect = Rect(pos.x + this->text.sprite_dimensions().x + 8, pos.y + 2, 128, 16);
				this->button.renderingPriority = 3;

				this->button.minValue 	= 0.0f;
				this->button.maxValue 	= 1.0f;
				this->button.value 		= Audio::GetCurrentGlobalVolume();
				this->button.renderingPriority = 5;
				break;
			}

			case (TOGGLE):
			{

			}

		}
	}

	void MainMenu::Setting::AddToScene(Scene* scene)
	{
		scene->AddObject(&this->text);
		scene->AddObject(&this->button);
	}
}
