#include "Entity.hpp"
#include "Logger.hpp"
#include "Values.hpp"

Birb2D::Entity::Sprite::Sprite() {}
Birb2D::Entity::Sprite::Sprite(std::string filePath)
{
	//texture.sdlTexture = Global::Renderer::mainWindow.loadTexture(filePath.c_str());
}

Birb2D::Entity::Text::Text() {}
Birb2D::Entity::Text::Text(std::string p_text, Birb2D::Font p_font, Rect p_frame, RenderWindow window)
:value(p_text), font(p_font)
{
	texture = window.Birb2D::RenderWindow::renderStaticTextTexture(value.c_str(), font);
	Debug::Log("Text dimensions: " + std::to_string(texture.dimensions.x) + ", " + std::to_string(texture.dimensions.y));
	frame = p_frame;
	
	if (texture.sdlTexture == NULL)
		Debug::Log("Could not render the texture for entity text! Text: [" + value + "].");
}

Birb2D::Entity::Entity() {}

Birb2D::Entity::Entity(std::string p_name, Vector2f p_position)
:name(p_name), rect(p_position.x, p_position.y, 0, 0)
{}

Birb2D::Entity::Entity(std::string p_name, Rect p_rect)
:name(p_name), rect(p_rect)
{}

Birb2D::Entity::Entity(std::string p_name, Rect p_rect, float p_angle)
:name(p_name), rect(p_rect), angle(p_angle)
{}

Birb2D::Entity::Entity(std::string p_name, Rect p_rect, float p_angle, Vector2f p_objectCenter)
:name(p_name), rect(p_rect), angle(p_angle), objectCenter(p_objectCenter)
{}

Birb2D::Entity::Entity(std::string p_name, Rect p_rect, float p_angle, Vector2f p_objectCenter, Vector2f p_anchor)
:name(p_name), rect(p_rect), angle(p_angle), objectCenter(p_objectCenter), anchor(p_anchor)
{}
