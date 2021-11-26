#include <string.h>
#include "Widgets.hpp"
#include "Font.hpp"
#include "Utils.hpp"
#include "Values.hpp"
#include "Logger.hpp"

Birb2D::Widgets::Position::Anchor::Anchor()
{
	x = 0, y = 0;
}

Birb2D::Widgets::Position::Center::Center()
{
	x = 0, y = 0;
}

Birb2D::Widgets::Position::Anchor::Anchor(float p_x, float p_y)
:x(p_x), y(p_y)
{}

Birb2D::Widgets::Position::Center::Center(float p_x, float p_y)
:x(p_x), y(p_y)
{}

/* ---- Centering and anchor stuff ---- */
//Birb2D::Widgets::Position::Position(Vector2f p_absolutePosition)
//:position(p_absolutePosition)
//{}
//
//Birb2D::Widgets::Position::Position(RenderWindow p_window, Anchor p_anchor, Center p_center, Vector2f p_offset)
//:window(p_window), anchor(p_anchor), center(p_center), position(p_offset)
//{
//	Vector2int winDimensions = p_window.getDimensions();
//	winDimensions.x *= anchor.x;
//	winDimensions.y *= anchor.y;
//
//}
/* ------------------------------------ */

Birb2D::Widgets::Button::Button(RenderWindow p_window, Rect p_dimensions, SDL_Colour p_backgroundColor, std::string p_text, Font p_font, std::function<void()> p_onClick, int p_z)
:font(p_font), text(p_text), window(p_window), originalDimensions(p_dimensions), backgroundColor(p_backgroundColor), onClick(p_onClick), z(p_z)
{
	dimensions = originalDimensions;
	Birb2D::Texture textTexture = window.renderStaticTextTexture(p_text.c_str(), p_font);
	if (textTexture.sdlTexture == NULL)
		Debug::Log("Error creating textTexture: " + (std::string)SDL_GetError(), Debug::error);

	//textEntity = Birb2D::Entity("Button", Vector2f(dimensions.x + 3, dimensions.y + 3), Vector2f(dimensions.w - 3, dimensions.h - 3), textTexture);
	textEntity = Birb2D::Entity("Button", Vector2f(dimensions.x + 3, dimensions.y + 3), Vector2f(textTexture.dimensions.x - 3, textTexture.dimensions.y - 3), textTexture);
	altBackgroundColor = Colors::ChangeColorIntensity(backgroundColor, -70);

	hoverDimensions.x = dimensions.x - 5;
	hoverDimensions.y = dimensions.y - 5;
	hoverDimensions.w = dimensions.w + 10;
	hoverDimensions.h = dimensions.h + 10;

	Debug::Log("Creating button...");
}


void Birb2D::Widgets::Button::refresh(Birb2D::Widgets::RefreshAction refreshAction)
{
	// Detect if hoving over the button and render the background
	switch (refreshAction)
	{
		case (Birb2D::Widgets::RefreshAction::Render):
			if (window.cursorInRect(originalDimensions))
			{
				// Hovering over the button
				dimensions = hoverDimensions;
				window.DrawRect(altBackgroundColor, dimensions);
			}
			else
			{
				// Not hovering over the button
				dimensions = originalDimensions;
				window.DrawRect(backgroundColor, dimensions);
			}
			
			// Render button text
			window.render(textEntity);
			break;

		case (Birb2D::Widgets::RefreshAction::Click):
			if (window.cursorInRect(dimensions))
				onClick();
			break;

		default:
			break;
	}
}

Birb2D::Widgets::Text::Text(RenderWindow p_window, Vector2f p_pos, std::string p_text, Font p_font, int p_z)
:window(p_window), pos(p_pos), text(p_text), font(p_font), z(p_z)
{
	Debug::Log("Creating text widget [" + p_text + "]");
	Texture textTexture = window.renderStaticTextTexture(p_text.c_str(), font);
	if (textTexture.sdlTexture == NULL)
		Debug::Log("Error creating textTexture: " + (std::string)SDL_GetError(), Debug::error);

	textEntity = Birb2D::Entity("Text", Vector2f(pos.x, pos.y), Vector2f(textTexture.dimensions.x, textTexture.dimensions.y), textTexture);
	Debug::Log("Text widget created!");
}

void Birb2D::Widgets::Text::render()
{
	window.render(textEntity);
}

Birb2D::Widgets::TopBar::TopBar(RenderWindow p_window, int barHeight, SDL_Color p_backgroundColor, Font font)
:window(p_window), backgroundColor(p_backgroundColor)
{
	dimensions.w = window.getDimensions().x;
	dimensions.h = barHeight;
	Texture textTexture = window.renderStaticTextTexture("Birb2D", font);
	if (textTexture.sdlTexture == NULL)
		Debug::Log("Error creating textTexture: " + (std::string)SDL_GetError(), Debug::error);

	Entity titleEntity("Title", Vector2f(5, 8), Vector2f(textTexture.dimensions.x, textTexture.dimensions.y), textTexture);
	title = titleEntity;
}

Birb2D::Widgets::Rectangle::Rectangle(RenderWindow p_window, Rect p_dimensions, SDL_Color p_backgroundColor, int p_z)
:window(p_window), dimensions(p_dimensions), backgroundColor(p_backgroundColor), z(p_z)
{

}

Rect Birb2D::Widgets::Rectangle::getDimensions()
{
	return dimensions;
}

SDL_Color Birb2D::Widgets::Rectangle::getBackgroundColor()
{
	return backgroundColor;
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
