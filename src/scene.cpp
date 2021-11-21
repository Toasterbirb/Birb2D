#include "../include/Scene.hpp"
#include "../include/Logger.hpp"

Birb2D::Scene::Scene(std::string p_name, Birb2D::RenderWindow p_window, bool p_enabled, int p_layers)
:name(p_name), window(p_window), enabled(p_enabled), layers(p_layers)
{

}

// Add a single button
void Birb2D::Scene::AddButton(Birb2D::Widgets::Button button)
{
	buttons.push_back(button);
}

// Add multiple buttons
void Birb2D::Scene::AddButton(std::vector<Birb2D::Widgets::Button> button)
{
	for (int i = 0; i < button.size(); i++)
		buttons.push_back(button[i]);
}

void Birb2D::Scene::AddText(Birb2D::Widgets::Text text)
{
	texts.push_back(text);
}

void Birb2D::Scene::AddText(std::vector<Birb2D::Widgets::Text> text)
{
	for (int i = 0; i < text.size(); i++)
		texts.push_back(text[i]);
}

void Birb2D::Scene::AddRectangle(Birb2D::Widgets::Rectangle rectangle)
{
	rectangles.push_back(rectangle);
}

void Birb2D::Scene::AddRectangle(std::vector<Birb2D::Widgets::Rectangle> rectangle)
{
	for (int i = 0; i < rectangle.size(); i++)
		rectangles.push_back(rectangle[i]);
}

void Birb2D::Scene::PollButtonEvents(SDL_Event event)
{
	if (enabled && event.type == SDL_MOUSEBUTTONDOWN)
	{
		for (int i = 0; i < (int)buttons.size(); i++)
		{
			buttons[i].refresh(Birb2D::Widgets::RefreshAction::Click);
		}
	}
}

void Birb2D::Scene::Render()
{
	// Render the secene only if its enabled, else just skip it
	if (enabled)
	{
		int z_index = -1;
		int maxLoopCount = buttons.size() + texts.size() + rectangles.size();

		// Layer stuff in batches of 1 layer at a time
		// 0 is rendered first and when that is done, increase the layer number
		// and so on.
		//
		// TODO: Optimize this thing to handle the layer count calculation automatically,
		// and maybe even get a list of layer numbers to skip the unused ones
		while (z_index < layers)
		{
			// Render buttons
			for (int i = 0; i < (int)buttons.size(); i++)
			{
				if (z_index == buttons[i].z)
				{
					buttons[i].refresh(Birb2D::Widgets::RefreshAction::Render);
				}
			}
			
			// Render text objects
			for (int i = 0; i < (int)texts.size(); i++)
			{
				if (z_index == texts[i].z)
				{
					texts[i].render();
				}
			}

			// Render rectangles
			for (int i = 0; i < (int)rectangles.size(); i++)
			{
				if (z_index == rectangles[i].z)
				{
					window.DrawRect(rectangles[i].getBackgroundColor(), rectangles[i].getDimensions());
				}
			}

			z_index++;
		}
	}
}

void Birb2D::Scene::enable()
{
	enabled = true;
}

void Birb2D::Scene::disable()
{
	enabled = false;
}

void Birb2D::Scene::toggle()
{
	if (enabled)
		enabled = false;
	else
		enabled = true;
}

bool Birb2D::Scene::isEnabled()
{
	return enabled;
}
