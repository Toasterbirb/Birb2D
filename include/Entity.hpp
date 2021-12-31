#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Utils.hpp"

namespace Birb2D
{
	struct TextComponent
	{
		TextComponent();
		TextComponent(std::string p_text, TTF_Font* font, SDL_Color* p_color);
		std::string text;
		TTF_Font* font;
		SDL_Color* color;
	};

	struct Entity
	{
		Entity();
		Entity(std::string p_name, Rect p_rect, SDL_Texture* p_texture);
		Entity(std::string p_name, Vector2int pos, TextComponent p_textComponent);
		Entity(std::string p_name, Vector2int pos, SDL_Texture* p_texture);

		std::string name;
		SDL_Texture* sprite;

		float angle;
		Rect rect;
		Vector2f localScale;

		TextComponent textComponent;
		void LoadSprite();
		void SetBaseEntityValues();
	};

}
