#include <string.h>
#include "../include/Widgets.hpp"
#include "../include/Font.hpp"
#include "../include/Utils.hpp"
#include "../include/Values.hpp"
#include "../include/Logger.hpp"

// Basic widget with no default text
Birb2D::Widgets::Widget::Widget(RenderWindow p_window, Birb2D::Widgets::WidgetType p_type, Rect p_dimensions, SDL_Color p_backgroundColor)
:window(p_window), type(p_type), dimensions(p_dimensions), backgroundColor(p_backgroundColor)
{
	font = Font("../res/fonts/freefont/FreeMono.ttf", 12);
	altBackgroundColor = Colors::ChangeColorIntensity(backgroundColor, -70);
}

// Widget with text
Birb2D::Widgets::Widget::Widget(RenderWindow p_window, Birb2D::Widgets::WidgetType p_type, Rect p_dimensions, SDL_Color p_backgroundColor, std::string p_text, Font p_font)
:window(p_window), type(p_type), font(p_font), dimensions(p_dimensions), backgroundColor(p_backgroundColor)
{
	Birb2D::Texture textTexture = window.renderStaticTextTexture(p_text.c_str(), p_font);
	text = Birb2D::Entity("Widget", Vector2f(dimensions.x, dimensions.y), Vector2f(dimensions.w, dimensions.h), textTexture);

	altBackgroundColor = Colors::ChangeColorIntensity(backgroundColor, -70);
}

void printHello()
{
	Debug::Log("Button click working");
}

// Widget with text and custom text dimensions
Birb2D::Widgets::Widget::Widget(RenderWindow p_window, Birb2D::Widgets::WidgetType p_type, Rect p_dimensions, SDL_Color p_backgroundColor, std::string p_text, Rect text_dimensions, Font p_font)
:window(p_window), type(p_type), font(p_font), dimensions(p_dimensions), backgroundColor(p_backgroundColor)
{
	Birb2D::Texture textTexture = window.renderStaticTextTexture(p_text.c_str(), p_font);
	text = Birb2D::Entity("Widget", Vector2f(text_dimensions.x + dimensions.x, text_dimensions.y + dimensions.y), Vector2f(text_dimensions.w, text_dimensions.h), textTexture);

	altBackgroundColor = Colors::ChangeColorIntensity(backgroundColor, -70);
	onClick = printHello;
}

Birb2D::Widgets::TopBar::TopBar(RenderWindow p_window, int barHeight, SDL_Color p_backgroundColor, Font font)
:window(p_window), backgroundColor(p_backgroundColor)
{
	dimensions.w = window.getDimensions().x;
	dimensions.h = barHeight;
	Texture textTexture = window.renderStaticTextTexture("Birb2D", font);

	Entity titleEntity("Title", Vector2f(5, 8), Vector2f(textTexture.dimensions.x, textTexture.dimensions.y), textTexture);
	title = titleEntity;
}

void Birb2D::Widgets::Widget::refresh(Birb2D::Widgets::RefreshAction refreshAction)
{
	// Handle different types of widgets
	switch (type)
	{
		case (Birb2D::Widgets::WidgetType::Button):
			// Detect if hoving over the button and render the background
			switch (refreshAction)
			{
				case (Birb2D::Widgets::RefreshAction::Render):
					if (window.cursorInRect(dimensions))
					{
						window.DrawRect(altBackgroundColor, dimensions);
					}
					else
					{
						window.DrawRect(backgroundColor, dimensions);
					}
					
					// Render button text
					window.render(text);
					break;

				case (Birb2D::Widgets::RefreshAction::Click):
					if (window.cursorInRect(dimensions))
						onClick();
					break;

				default:
					break;
			}


			break;

		default:
			break;
	}
}

void Birb2D::Widgets::TopBar::refresh(Vector2int windowDimensions)
{
	dimensions.w = windowDimensions.x;
	dimensions.x = 0;
	dimensions.y = 0;

	window.DrawRect(Colors::White, dimensions);
	window.DrawRect(Colors::LightGray, Rect(dimensions.x, (dimensions.h / 5) * 4 + 1, dimensions.w, dimensions.h / 5));
	window.render(title);
}
