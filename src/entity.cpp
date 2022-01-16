#include "Logger.hpp"
#include "Entity.hpp"
#include "Renderwindow.hpp"

namespace Birb2D
{
	TextComponent::TextComponent()
	{
		text = "";
		font = NULL;
		color = NULL;
	}

	TextComponent::TextComponent(std::string p_text, TTF_Font* p_font, SDL_Color* p_color)
	:text(p_text), font(p_font), color(p_color)
	{}

	void Entity::SetText(std::string newText)
	{
		/* Don't do anything if the text hasn't changed at all */
		if (textComponent.text == newText)
			return;

		/* Destroy the old sprite */
		SDL_DestroyTexture(sprite);

		/* Create new text sprite */
		textComponent.text = newText;
		LoadSprite();
	}

	void Entity::SetBaseEntityValues()
	{
		angle = 0;
		localScale = Vector2f(1, 1);
	}

	Entity::Entity(std::string p_name, Rect p_rect, SDL_Texture* p_texture)
	:name(p_name), sprite(p_texture), rect(p_rect)
	{
		SetBaseEntityValues();
	}

	Entity::Entity(std::string p_name, Vector2int pos, TextComponent p_textComponent)
	:name(p_name)
	{
		/* Load the text sprite */
		SetBaseEntityValues();
		textComponent = p_textComponent;
		LoadSprite();

		rect.x = pos.x;
		rect.y = pos.y;

	}

	Entity::Entity(std::string p_name, Vector2int pos, SDL_Texture* p_texture)
	:name(p_name), sprite(p_texture)
	{
		SetBaseEntityValues();
		rect.x = pos.x;
		rect.y = pos.y;

		/* Get texture scale automatically */
		int w, h;
		utils::GetTextureDimensions(p_texture, w, h);
		rect.w = w;
		rect.h = h;
	}

	void Entity::LoadSprite()
	{
		/* There's a text component. Let's generate a text sprite for it */
		if (textComponent.text != "")
		{
			//Debug::Log("Loading a text sprite '" + name + "'");
			sprite = Resources::TextSprite(textComponent.text, textComponent.font, *textComponent.color);

			if (sprite == nullptr)
				Debug::Log("Something went wrong while creating the text sprite for '" + name + "'", Debug::error);
			else
			{
				/* Get texture scale automatically */
				int w, h;
				utils::GetTextureDimensions(sprite, w, h);
				rect.w = w;
				rect.h = h;
			}
		}
	}
}
