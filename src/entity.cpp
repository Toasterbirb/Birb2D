#include <stdio.h>
#include "../include/Entity.hpp"

// Normal texture entity
Entity::Entity(const char* p_name, Vector2f p_pos, Vector2f p_dimensions, SDL_Texture* p_tex)
:name(p_name), pos(p_pos), tex(p_tex)
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
Entity::Entity(const char* p_name, Vector2f p_pos, Vector2f p_dimensions, float p_angle, SDL_Texture* p_tex)
:name(p_name), pos(p_pos), tex(p_tex), angle(p_angle)
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
Entity::Entity(const char* p_name, Vector2f p_pos, float p_scaleMultiplier, Vector2f p_dimensions, SDL_Texture* p_tex)
:name(p_name), pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_dimensions.x * p_scaleMultiplier;
	currentFrame.h = p_dimensions.y * p_scaleMultiplier;
	angle = 0;

	pos_rect.x = p_pos.x;
	pos_rect.y = p_pos.y;
	pos_rect.w = currentFrame.w;
	pos_rect.h = currentFrame.h;
}

// Scalable texture entity with custom angle
Entity::Entity(const char* p_name, Vector2f p_pos, float p_scaleMultiplier, Vector2f p_dimensions, float p_angle, SDL_Texture* p_tex)
:name(p_name), pos(p_pos), tex(p_tex), angle(p_angle)
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

SDL_Texture* Entity::getTex()
{
	return tex;
}

Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

// Text entity
Entity::Entity(const char* p_name, std::string p_text, Vector2f p_pos, Font* p_font)
:name(p_name), pos(p_pos), text(p_text), font(p_font)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = font->getSize() * p_text.length() - font->getSize();
	currentFrame.h = font->getSize();
	angle = 0;
}

// Text entity with custom angle and texture
Entity::Entity(const char* p_name, std::string p_text, Vector2f p_pos, Font* p_font, SDL_Texture* p_tex, float p_angle)
:name(p_name), pos(p_pos), text(p_text), font(p_font), angle(p_angle), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = font->getSize() * p_text.length() - font->getSize();
	currentFrame.h = font->getSize();
}

// Update the text of an existing text entity
void Entity::updateText(std::string p_text, SDL_Texture* p_tex)
{
	if (p_text != text)
	{
		// Set text
		text = p_text;

		currentFrame.x = 0;
		currentFrame.y = 0;
		currentFrame.w = font->getSize() * p_text.length() - font->getSize();
		currentFrame.h = font->getSize();

		// Set texture
		tex = p_tex;
	}
}

Vector2f& Entity::getPos()
{
	return pos;
}

// Set the position of an entity
void Entity::setPos(Vector2f p_pos)
{
	pos = p_pos;
	pos_rect.x = p_pos.x;
	pos_rect.y = p_pos.y;
	pos_rect.w = currentFrame.w;
	pos_rect.h = currentFrame.h;
}

Rect* Entity::getRect()
{
	return &pos_rect;
}

float& Entity::getAngle()
{
	return angle;
}

void Entity::setAngle(float p_angle)
{
	angle = p_angle;
}

Font* Entity::getFont()
{
	return font;
}

std::string Entity::getText()
{
	return text;
}

std::string Entity::getName()
{
	return name;
}
