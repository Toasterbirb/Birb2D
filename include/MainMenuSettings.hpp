#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <string>
#include <vector>
#include <cassert>
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

		struct Window
		{
			Window();
			Font 		title_font;
			Color 		title_color;
			Rect 		top_bar;
			Rect 		background;

			Color 		text_color;
		};

		struct Settings
		{
			Settings();
			Window 		window;
			Font 		setting_font;

			Color 		slider_fill_color;
			Color 		slider_background_color;
			Color 		slider_border_color;
		};

		struct Credits
		{
			Credits();
			Window 		window;
			Font 		text_font;
			std::string credits_text;
		};

		Settings 	settings_menu;
		Credits 	credits_menu;

		Texture background_texture;
		Color background_color;

	private:
		static Font default_font;
	};
}
