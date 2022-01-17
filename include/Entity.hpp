#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Utils.hpp"

namespace Birb2D
{
	///
	/// TextComponent contains details needed to generate a sprite for the Entity in case the Entity is used to display text.
	///
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
		Entity(); /*!< Creates empty Entity object */
		Entity(std::string p_name, Rect p_rect, SDL_Texture* p_texture); /*!< Creates an Entity with a SDL_Texture to render with custom scale */
		Entity(std::string p_name, Vector2int pos, TextComponent p_textComponent); /*!< Creates a Text Entity using a TextComponent */
		Entity(std::string p_name, Vector2int pos, SDL_Texture* p_texture); /*!< Creates an Entity with a SDL_Texture to render without specifying a scale */

		/* Make it possible to update the TextComponent */
		void SetText(std::string newText);
		void SetFont(TTF_Font* font);
		void SetColor(SDL_Color* color);

		std::string name;
		SDL_Texture* sprite;

		float angle;
		Rect rect;
		Vector2f localScale;

		TextComponent textComponent; /*!< Having a TextComponent in an Entity enables the rendering of Text */
		void LoadSprite();
		void ReloadSprite();
		void SetBaseEntityValues();
	};

}
