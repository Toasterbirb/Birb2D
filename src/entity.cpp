#include <stdio.h>
#include "../include/Entity.hpp"
#include "../include/Widgets.hpp"
#include "../include/Values.hpp"

// Default empty entity
Birb2D::Entity::Entity()
{
	name = "";
	pos = Vector2f(0, 0);
	angle = 0;
	text = "";
	Birb2D::Font defaultFont("../res/fonts/manaspace/manaspc.ttf", Colors::White, 32);
	font = defaultFont;
	tex = NULL;
}

// Normal texture entity
Birb2D::Entity::Entity(const char* p_name, Vector2f p_pos, Vector2f p_dimensions, Texture p_tex)
:name(p_name), pos(p_pos), tex(p_tex.sdlTexture)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_dimensions.x;
	currentFrame.h = p_dimensions.y;
	angle = 0;

	pos_rect.x = p_pos.x;
	pos_rect.y = p_pos.y;
	pos_rect.w = currentFrame.w;
	pos_rect.h = currentFrame.h;
}

// Normal texture entity
Birb2D::Entity::Entity(const char* p_name, Vector2f p_pos, Vector2f p_dimensions, float p_angle, Texture p_tex)
:name(p_name), pos(p_pos), tex(p_tex.sdlTexture), angle(p_angle)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_dimensions.x;
	currentFrame.h = p_dimensions.y;

	pos_rect.x = p_pos.x;
	pos_rect.y = p_pos.y;
	pos_rect.w = currentFrame.w;
	pos_rect.h = currentFrame.h;
}

// Scalable texture entity
Birb2D::Entity::Entity(const char* p_name, Vector2f p_pos, float p_scaleMultiplier, Vector2f p_dimensions, Texture p_tex)
:name(p_name), pos(p_pos), tex(p_tex.sdlTexture), localScale(p_scaleMultiplier)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_dimensions.x;
	currentFrame.h = p_dimensions.y;
	angle = 0;

	pos_rect.x = p_pos.x;
	pos_rect.y = p_pos.y;
	pos_rect.w = currentFrame.w;
	pos_rect.h = currentFrame.h;
}

// Scalable texture entity with custom angle
Birb2D::Entity::Entity(const char* p_name, Vector2f p_pos, float p_scaleMultiplier, Vector2f p_dimensions, float p_angle, SDL_Texture* p_tex)
:name(p_name), pos(p_pos), tex(p_tex), angle(p_angle), localScale(p_scaleMultiplier)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_dimensions.x * p_scaleMultiplier;
	currentFrame.h = p_dimensions.y * p_scaleMultiplier;

	pos_rect.x = p_pos.x;
	pos_rect.y = p_pos.y;
	pos_rect.w = currentFrame.w;
	pos_rect.h = currentFrame.h;
}

SDL_Texture* Birb2D::Entity::getTex()
{
	return tex;
}

Rect Birb2D::Entity::getCurrentFrame()
{
	return currentFrame;
}

// Text entity
Birb2D::Entity::Entity(const char* p_name, std::string p_text, Vector2f p_pos, Birb2D::Font p_font)
:name(p_name), pos(p_pos), text(p_text), font(p_font)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = font.getSize() * p_text.length() - font.getSize();
	currentFrame.h = font.getSize();
	angle = 0;
}

// Text entity with custom angle and texture
Birb2D::Entity::Entity(const char* p_name, std::string p_text, Vector2f p_pos, Birb2D::Font p_font, SDL_Texture* p_tex, float p_angle)
:name(p_name), pos(p_pos), text(p_text), font(p_font), angle(p_angle), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = font.getSize() * p_text.length() - font.getSize();
	currentFrame.h = font.getSize();
}

// Update the text of an existing text entity
void Birb2D::Entity::updateText(std::string p_text, SDL_Texture* p_tex)
{
	if (p_text != text)
	{
		// Set text
		text = p_text;

		currentFrame.x = 0;
		currentFrame.y = 0;
		currentFrame.w = font.getSize() * p_text.length() - font.getSize();
		currentFrame.h = font.getSize();

		// Set texture
		tex = p_tex;
	}
}

Vector2f& Birb2D::Entity::getPos()
{
	return pos;
}

// Set the position of an entity
void Birb2D::Entity::setPos(Vector2f p_pos)
{
	pos = p_pos;
	pos_rect.x = p_pos.x;
	pos_rect.y = p_pos.y;
	pos_rect.w = currentFrame.w;
	pos_rect.h = currentFrame.h;
}

Rect* Birb2D::Entity::getRect()
{
	return &pos_rect;
}

float& Birb2D::Entity::getAngle()
{
	return angle;
}

void Birb2D::Entity::setAngle(float p_angle)
{
	angle = p_angle;
}

Birb2D::Font Birb2D::Entity::getFont()
{
	return font;
}

std::string Birb2D::Entity::getText()
{
	return text;
}

std::string Birb2D::Entity::getName()
{
	return name;
}
