#include "Diagnostics.hpp"
#include "Entity.hpp"
#include "Logger.hpp"
#include "Renderwindow.hpp"
#include "Values.hpp"

namespace Birb
{
	Vector2Int Entity::getAtlasPosition(const int& frame)
	{
		Vector2Int pos;
		int index = frame;

		int texWidth;
		//int texHeight;
		texWidth = sprite.dimensions().x;
		//texHeight = sprite.dimensions().y;

		int spritesPerRow = texWidth / animationComponent.spriteSize.x;
		float fullRowCount = std::floor(index / spritesPerRow);
		float leftOver = ((index / static_cast<float>(spritesPerRow)) - fullRowCount) * spritesPerRow;

		pos.x = leftOver * animationComponent.spriteSize.x;
		pos.y = fullRowCount * animationComponent.spriteSize.y;

		return pos;
	}

	bool Entity::SetText(const std::string& newText)
	{
		/* Don't do anything if the text hasn't changed at all */
		if (textComponent.text == newText)
			return true;

		textComponent.text = newText;
		return ReloadSprite();
	}

	void Entity::SetFont(const Font& font)
	{
		/* Don't do anything if the font hasn't changed at all */
		if (textComponent.font == &font)
			return;

		*textComponent.font = font;
		ReloadSprite();
	}

	void Entity::SetColor(Color* color)
	{
		/* Don't do anything if the color hasn't changed at all */
		if (color->a == textComponent.color->a
			&& color->r == textComponent.color->r
			&& color->g == textComponent.color->g
			&& color->b == textComponent.color->b) return;

		textComponent.color = color;
		ReloadSprite();
	}

	void Entity::SetBaseEntityValues()
	{
		angle = 0;
		localScale = Vector2(1, 1);
		active = true;
	}

	void Entity::CenterRelativeTo(const Rect& rect)
	{
		Vector2Int textureDimensions = sprite.dimensions();
		this->rect.x = ((rect.w / 2) - (textureDimensions.x / 2.0)) + rect.x;
		this->rect.y = ((rect.h / 2) - (textureDimensions.y / 2.0)) + rect.y;
	}

	Entity::Entity()
	{
		name = "Default Entity";
		SetBaseEntityValues();
	}

	Entity::Entity(const std::string& p_name)
	:name(p_name)
	{
		SetBaseEntityValues();
	}

	/* FIXME: Write tests for this constructor */
	Entity::Entity(const std::string& p_name, const Rect& rect)
	:name(p_name), rect(rect)
	{
		SetBaseEntityValues();
	}

	Entity::Entity(const std::string& name, const Rect& rect, Texture texture)
	:name(name), rect(rect), sprite(texture)
	{
		SetBaseEntityValues();
	}

	Entity::Entity(const std::string& name, const Vector2Int& pos, Texture texture)
	:name(name), sprite(texture)
	{
		SetBaseEntityValues();
		rect.x = pos.x;
		rect.y = pos.y;

		/* Get texture scale automatically */
		rect.w = texture.dimensions().x;
		rect.h = texture.dimensions().y;
	}

	Entity::Entity(const std::string& name, const Vector2Int& pos, Texture texture, const EntityComponent::Animation& animationComponent)
	:name(name), sprite(texture), animationComponent(animationComponent)
	{
		/* Load the text sprite */
		SetBaseEntityValues();
		//this->animationComponent = animationComponent;

		rect.x = pos.x;
		rect.y = pos.y;
		rect.w = animationComponent.spriteSize.x;
		rect.h = animationComponent.spriteSize.y;
	}

	Entity::Entity(const std::string& p_name, const Vector2Int& pos, const EntityComponent::Text& p_textComponent)
	:name(p_name)
	{
		/* Load the text sprite */
		SetBaseEntityValues();
		textComponent = p_textComponent;
		LoadSprite();

		rect.x = pos.x;
		rect.y = pos.y;

	}


	bool Entity::LoadSprite()
	{
		/* There's a text component. Let's generate a text sprite for it */
		if (textComponent.text != "")
		{
			if (textComponent.bgColor == NULL)
				sprite = Resources::TextSprite(textComponent.text, *textComponent.font, *textComponent.color, textComponent.wrapLength);
			else
				sprite = Resources::TextSprite(textComponent.text, *textComponent.font, *textComponent.color, *textComponent.bgColor);

			if (sprite.isLoaded() == false)
			{
				Debug::Log("Something went wrong while creating the text sprite for '" + name + "'", Debug::error);
				return false;
			}
			else
			{
				/* Get texture scale automatically */
				rect.w = sprite.dimensions().x;
				rect.h = sprite.dimensions().y;
			}
		}

		return true;
	}

	bool Entity::ReloadSprite()
	{
		/* Destroy the old sprite */
		sprite.Destroy();

		/* Create new text sprite */
		return LoadSprite();
	}

	void Entity::RenderFunc()
	{
		Render::DrawEntity(*this);
	}

	void Entity::SetPos(const Vector2& delta)
	{
		rect.x += delta.x;
		rect.y += delta.y;
	}
}
