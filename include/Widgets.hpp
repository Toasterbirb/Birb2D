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

		enum RefreshAction
		{
			Render, Click
		};

		class Position
		{
			// Eggsample:
			// Center = 0,0
			// Anchor = 0,0
			// Widget should be positioned to the top left corner
			
			// Eggsample2:
			// Center = 1,0
			// Anchor = 1,0
			// Widget should be positioned to the top right corner


			public:
				// Anchor position in window that the center point is moved relatively to
				struct Anchor
				{
					Anchor(float p_x, float p_y);
					float x, y;
				};

				// Center point of the widget that the position sets
				struct Center
				{
					Center(float p_x, float p_y);
					float x, y;
				};
				Position(Anchor p_anchor, Center p_center);
				Position(Anchor p_anchor, Center p_center, Vector2f p_offset);
				Position(Vector2f p_anchor, Vector2f p_center);
				Position(Vector2f p_anchor, Vector2f p_center, Vector2f p_offset);

			private:
				Anchor anchor;
				Center center;
				Vector2f offset;
		};

		class Button
		{
			public:
				Button(RenderWindow p_window, Rect p_dimensions, SDL_Color p_backgroundColor, std::string p_text, Font p_font, std::function<void()> p_onClick, int p_z = 0);
				void refresh(RefreshAction refreshAction);
				int z;

			private:
				Font font;
				std::string text;
				Entity textEntity;
				RenderWindow window;
				Rect dimensions;
				Rect originalDimensions;
				Rect hoverDimensions;
				SDL_Color backgroundColor;
				SDL_Color altBackgroundColor;
				std::function<void()> onClick;
		};

		class Text
		{
			public:
			   	Text(RenderWindow p_window, Vector2f location, std::string p_text, Font p_font, int p_z = 0);
				void render();
				int z;

			private:
				RenderWindow window;
				Vector2f pos;
				Font font;
				std::string text;
				Entity textEntity;
		};

		class Rectangle
		{
			public:
				Rectangle(RenderWindow p_window, Rect p_dimensions, SDL_Color p_backgroundColor, int p_z = 0);
				Rect getDimensions();
				SDL_Color getBackgroundColor();
				int z;

			private:
				RenderWindow window;
				Rect dimensions;
				SDL_Color backgroundColor;
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
