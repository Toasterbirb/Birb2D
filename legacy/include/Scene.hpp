#pragma once
#include <vector>
#include "../include/RenderWindow.hpp"
#include "../include/Widgets.hpp"


namespace Birb2D
{
	class Scene
	{
		public:
			Scene();
			Scene(std::string p_name, Birb2D::RenderWindow p_window, bool p_enabled = false, int p_layers = 1);
			void AddButton(Widgets::Button button);
			void AddButton(std::vector<Widgets::Button> buttons);
			void AddText(Widgets::Text text);
			void AddText(std::vector<Widgets::Text> text);
			void AddRectangle(Widgets::Rectangle rectangle);
			void AddRectangle(std::vector<Widgets::Rectangle> rectangle);
			void PollButtonEvents(SDL_Event event);
			void Render();
			void enable();
			void disable();
			void toggle();
			bool isEnabled();

		private:
			std::string name;
			RenderWindow window;
			std::vector<Birb2D::Widgets::Button> buttons;
			std::vector<Birb2D::Widgets::Text> texts;
			std::vector<Birb2D::Widgets::Rectangle> rectangles;
			std::vector<Birb2D::Entity> entities;
			bool enabled;
			int layers;
	};
}
