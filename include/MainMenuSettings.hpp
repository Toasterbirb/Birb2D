#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <string>
#include <vector>
#endif

#include "Color.hpp"
#include "Font.hpp"
#include "Rect.hpp"
#include "Texture.hpp"
#include "Vector/Vector2Int.hpp"

namespace Birb
{
	class MainMenuSettings
	{
	public:
		MainMenuSettings();

		struct Title
		{
			Font 		font;
			std::string text;
			Vector2Int 	position;
			Color 		color;
		};

		Title title;

		struct Button
		{
			Button();
			Font 		font;
			Color 		text_color;
			Color 		background_color;
			Color 		highlight_color;
			Rect 		rect;
			Rect 		button_background;
			std::string text;
		};

		Button play, settings, credits, quit;
		int button_text_padding;
		std::vector<Button*> buttons;

		enum ButtonName
		{
			PLAY 		= 0,
			SETTINGS 	= 1,
			CREDITS 	= 2,
			QUIT 		= 3
		};

		struct Settings
		{
			Settings();
			Font 		title_font;
			Color 		title_color;

			Font 		setting_font;
			Color 		setting_color;

			Rect 		background;
			Rect 		top_bar;

			Color 		slider_fill_color;
			Color 		slider_background_color;
			Color 		slider_border_color;
		};

		Settings settings_menu;

		Texture background_texture;
		Color background_color;

	private:
		static Font default_font;
	};
}
