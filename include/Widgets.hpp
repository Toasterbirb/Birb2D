#pragma once
#include "../include/Entity.hpp"
#include "../include/Utils.hpp"
#include "../include/RenderWindow.hpp"
#include <vector>
#include <functional>

namespace Birb2D
{
	namespace Widgets
	{
		enum WidgetType
		{
			PlaceHolder, Button, Label, Slider, Picture, Dropdown
		};

		enum RefreshAction
		{
			Render, Click
		};

		class Widget
		{
			public:
				Widget(RenderWindow p_window, WidgetType type, Rect p_dimensions, SDL_Color p_backgroundColor);
				Widget(RenderWindow p_window, WidgetType type, Rect p_dimensions, SDL_Color p_backgroundColor, std::string p_text, Font p_font);
				Widget(RenderWindow p_window, WidgetType type, Rect p_dimensions, SDL_Color p_backgroundColor, std::string p_text, Rect text_dimensions, Font p_font);
				WidgetType getType()
				{
					return type;
				}
				void refresh(RefreshAction refreshAction);

			private:
				WidgetType type;
				Font font;
				Entity text;
				Rect dimensions;
				RenderWindow window;
				SDL_Color backgroundColor;
				SDL_Color altBackgroundColor;
				std::function<void()> onClick;
		};

		class TopBar
		{
			public:
				TopBar(RenderWindow p_window, int barHeight, SDL_Color p_backgroundColor, Font font);
				void refresh(Vector2int windowDimensions);

			private:
				Entity title;
				Rect dimensions;
				RenderWindow window;
				SDL_Color backgroundColor;
		};

	}
}
