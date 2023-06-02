#include "MainMenuSettings.hpp"
#include <vector>

namespace Birb
{
	MainMenuSettings::MainMenuSettings()
	{
		/* Populate the button array */
		buttons = std::vector<Button*>
		{
			&play, &settings, &credits, &quit
		};

		/* Set some default values */
		title.font.LoadFont("birb2d_res/fonts/manaspace/manaspc.ttf", 55);
		assert(title.font.isLoaded());
		title.text 		= "Placeholder title";
		title.position 	= Vector2Int(64, 64);
		title.color 	= Colors::Nord::SnowStorm::nord4;

		int button_offset = 16;
		play.rect.y 		= 400;
		settings.rect.y 	= play.rect.y + play.rect.h + button_offset;
		credits.rect.y 		= settings.rect.y + settings.rect.h + button_offset;
		quit.rect.y 		= credits.rect.y + credits.rect.h + button_offset;


		/* Set default button texts */
		play.text 		= "Play";
		settings.text 	= "Settings";
		credits.text 	= "Credits";
		quit.text 		= "Quit";

		/* Update button background dimensions */
		for (size_t i = 0; i < buttons.size(); ++i)
			buttons[i]->button_background = buttons[i]->rect;

		button_text_padding = 18;

		/* Set default background color in-case the background texture hasn't been set */
		background_color = Colors::Nord::PolarNight::nord0;
	}

	MainMenuSettings::Button::Button()
	{
		font.LoadFont("birb2d_res/fonts/manaspace/manaspc.ttf", 32);
		assert(font.isLoaded());
		text_color 			= Colors::Nord::SnowStorm::nord6;
		background_color 	= Colors::Nord::PolarNight::nord2;
		highlight_color 	= Colors::Nord::Aurora::nord15;

		rect.x = 64;
		rect.y = 0;
		rect.w = 128;
		rect.h = 44;
		rect.color = background_color;
		button_background = rect;
		button_background.renderingPriority = 1;

		text = "Button";
	}

	MainMenuSettings::Window::Window()
	{
		title_font.LoadFont("birb2d_res/fonts/manaspace/manaspc.ttf", 24);
		assert(title_font.isLoaded());
		title_color 	= Colors::Nord::Frost::nord9;

		background = Rect(500, 420, 300, 100);
		background.color = Colors::Nord::PolarNight::nord1;
		background.renderingPriority = 2;

		top_bar = Rect(background.x, background.y, background.w, 32);
		top_bar.color = Colors::Nord::PolarNight::nord2;
		top_bar.renderingPriority = 3;

		text_color 		= Colors::Nord::Frost::nord7;
	}

	MainMenuSettings::Settings::Settings()
	{
		setting_font.LoadFont("birb2d_res/fonts/manaspace/manaspc.ttf", 20);
		assert(setting_font.isLoaded());

		slider_fill_color 		= Colors::Nord::Aurora::nord14;
		slider_background_color = Colors::Nord::PolarNight::nord3;
		slider_border_color 	= Colors::Nord::Frost::nord7;
	}

	MainMenuSettings::Credits::Credits()
	{
		credits_text 			= "Someone really cool made this game";
		text_font.LoadFont("birb2d_res/fonts/manaspace/manaspc.ttf", 16);
		assert(text_font.isLoaded());
	}
}
