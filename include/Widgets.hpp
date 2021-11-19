#pragma once
#include "../include/Entity.hpp"
#include "../include/Utils.hpp"
#include "../include/RenderWindow.hpp"

namespace Widget
{
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

	namespace Colors
	{
		static SDL_Color White = 	{ 255, 255, 255 };
		static SDL_Color Black = 	{ 0, 0, 0 };
		static SDL_Color Red = 		{ 255, 0, 0 };
		static SDL_Color Green = 	{ 0, 255, 0 };
		static SDL_Color Blue = 	{ 0, 0, 255 };
	}
}
