#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Utils.hpp"

namespace Birb
{
	/// TextComponent contains details needed to generate a sprite for the Entity in case the Entity is used to display text.
	struct TextComponent
	{
		TextComponent();
		TextComponent(std::string p_text, TTF_Font* font, SDL_Color* p_color);
		std::string text;
		TTF_Font* font;
		SDL_Color* color; 	///< Surface color of the text
	};

	/// Entities are objects that contain all of the information required to render stuff
	
	/// Entities can be anything really. For example, it could be text or a picture. This could be extended to animations in the future
	struct Entity
	{
		Entity(); ///< Creates empty Entity object
		Entity(std::string p_name, Rect p_rect, SDL_Texture* p_texture); 			///< Creates an Entity with a SDL_Texture to render with custom scale
		Entity(std::string p_name, Vector2int pos, TextComponent p_textComponent); 	///< Creates a Text Entity using a TextComponent
		Entity(std::string p_name, Vector2int pos, SDL_Texture* p_texture); 		///< Creates an Entity with a SDL_Texture to render without specifying a scale

		/* Make it possible to update the TextComponent */
		void SetText(std::string newText); 	///< Change the text in TextComponent and reload the sprite
		void SetFont(TTF_Font* font); 		///< Change the font in TextComponent and reload the sprite
		void SetColor(SDL_Color* color); 	///< Change the color in TextComponent and reload the sprite

		std::string name; 		///< Name of the entity. Used for debugging
		SDL_Texture* sprite; 	///< Sprite to be rendered

		float angle; 			///< Sets the rotation of the entity when rendering it
		Rect rect; 				///< Sets the position and the dimensions of the entity
		Vector2f localScale; 	///< Scale modifier for the Entity rendering

		TextComponent textComponent; 	///< Having a TextComponent in an Entity enables the rendering of Text
		void LoadSprite(); 				///< Create a sprite for the Entity using details found in the textComponent variable
		void ReloadSprite(); 			///< Destroy the old sprite and create a new one. Useful for refreshing text after editing the textComponent variable
		void SetBaseEntityValues(); 	///< Used to set some default value when they aren't provided during Entity initialization
	};

}
