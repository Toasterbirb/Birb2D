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

	SDL_Rect new_pos_rect;
	new_pos_rect.x = p_pos.x;
	new_pos_rect.y = p_pos.y;
	new_pos_rect.w = currentFrame.w;
	new_pos_rect.h = currentFrame.h;
	pos_rect = new_pos_rect;
}

// Normal texture entity
Entity::Entity(const char* p_name, Vector2f p_pos, Vector2f p_dimensions, float p_angle, SDL_Texture* p_tex)
:name(p_name), pos(p_pos), tex(p_tex), angle(p_angle)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_dimensions.x;
	currentFrame.h = p_dimensions.y;

	SDL_Rect new_pos_rect;
	new_pos_rect.x = p_pos.x;
	new_pos_rect.y = p_pos.y;
	new_pos_rect.w = currentFrame.w;
	new_pos_rect.h = currentFrame.h;
	pos_rect = new_pos_rect;
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

	SDL_Rect new_pos_rect;
	new_pos_rect.x = p_pos.x;
	new_pos_rect.y = p_pos.y;
	new_pos_rect.w = currentFrame.w;
	new_pos_rect.h = currentFrame.h;
	pos_rect = new_pos_rect;
}

// Scalable texture entity
Entity::Entity(const char* p_name, Vector2f p_pos, float p_scaleMultiplier, Vector2f p_dimensions, float p_angle, SDL_Texture* p_tex)
:name(p_name), pos(p_pos), tex(p_tex), angle(p_angle)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_dimensions.x * p_scaleMultiplier;
	currentFrame.h = p_dimensions.y * p_scaleMultiplier;
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

SDL_Rect Entity::getCurrentFrame()
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

// Text entity
Entity::Entity(const char* p_name, std::string p_text, Vector2f p_pos, Font* p_font, SDL_Texture* p_tex, float p_angle)
:name(p_name), pos(p_pos), text(p_text), font(p_font), angle(p_angle), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = font->getSize() * p_text.length() - font->getSize();
	currentFrame.h = font->getSize();
}

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

void Entity::setPos(Vector2f p_pos)
{
	pos = p_pos;
	SDL_Rect new_pos_rect;
	new_pos_rect.x = p_pos.x;
	new_pos_rect.y = p_pos.y;
	new_pos_rect.w = currentFrame.w;
	new_pos_rect.h = currentFrame.h;
	pos_rect = new_pos_rect;
}

SDL_Rect* Entity::getRect()
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
