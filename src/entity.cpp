#include "Logger.hpp"
#include "Entity.hpp"
#include "Renderwindow.hpp"

namespace Birb
{
	namespace EntityComponent
	{
		TextComponent::TextComponent()
		{
			text 	= "";
			font 	= NULL;
			color 	= NULL;
			bgColor = NULL;
		}

		TextComponent::TextComponent(std::string p_text, TTF_Font* p_font, SDL_Color* p_color)
		:text(p_text), font(p_font), color(p_color)
		{
			bgColor = NULL;
		}

		TextComponent::TextComponent(std::string p_text, TTF_Font* p_font, SDL_Color* p_color, SDL_Color* p_bgColor)
		:text(p_text), font(p_font), color(p_color), bgColor(p_bgColor)
		{}

		void PlaceHolderClickEvent()
		{
			Debug::Log("This button is working");
		}

		ClickComponent::ClickComponent()
		{
			active = true;
			onClick = PlaceHolderClickEvent;
		}

		ClickComponent::ClickComponent(std::function<void()> p_onClick)
		:onClick(p_onClick)
		{
			active = true;
		}

		AnimationComponent::AnimationComponent()
		{
			fps 			= 24;
			loop 			= false;
			frameIndex 		= 0;
			frameCount 		= 0;
			spriteSize 		= { 16, 16 };
			animationQueued = false;
		}

		AnimationComponent::AnimationComponent(Vector2int p_spriteSize, int p_frameCount, int p_fps)
		:spriteSize(p_spriteSize), frameCount(p_frameCount), fps(p_fps), lastFrame(p_frameCount - 1)
		{
			frameIndex 		= 0;
			loop 			= false;
			animationQueued = false;
		}

		AnimationComponent::AnimationComponent(Vector2int p_spriteSize, int p_frameCount, int p_fps, bool p_loop)
		:spriteSize(p_spriteSize), frameCount(p_frameCount), fps(p_fps), loop(p_loop), lastFrame(p_frameCount - 1)
		{
			frameIndex 		= 0;
			animationQueued = false;
		}


		void AnimationComponent::ResetAnimationAtlas()
		{
			frameIndex = 0;
			lastFrame = frameCount - 1;
		}

		void AnimationComponent::StartAnimation()
		{
			ResetAnimationAtlas();
			animationQueued = true;
		}

		void AnimationComponent::StartAnimation(int p_startFrame)
		{
			frameIndex = p_startFrame;
			lastFrame = frameCount - 1;
			animationQueued = true;
		}

		void AnimationComponent::StartAnimation(int p_startFrame, int p_lastFrame)
		{
			frameIndex = p_startFrame;
			lastFrame = p_lastFrame;
			animationQueued = true;
		}
	}

	Vector2int Entity::getAtlasPosition(int frame)
	{
		Vector2int pos;
		int index = frame;

		int texWidth;
		int texHeight;
		SDL_QueryTexture(sprite, NULL, NULL, &texWidth, &texHeight);

		int spritesPerRow = texWidth / animationComponent.spriteSize.x;
		float fullRowCount = std::floor(index / spritesPerRow);
		float leftOver = ((index / (float)spritesPerRow) - fullRowCount) * spritesPerRow;

		pos.x = leftOver * animationComponent.spriteSize.x;
		pos.y = fullRowCount * animationComponent.spriteSize.y;

		return pos;
	}

	void Entity::SetText(std::string newText)
	{
		/* Don't do anything if the text hasn't changed at all */
		if (textComponent.text == newText)
			return;

		textComponent.text = newText;
		ReloadSprite();
	}

	void Entity::SetFont(TTF_Font* font)
	{
		/* Don't do anything if the font hasn't changed at all */
		if (textComponent.font == font)
			return;

		textComponent.font = font;
		ReloadSprite();
	}

	void Entity::SetColor(SDL_Color* color)
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
		localScale = Vector2f(1, 1);
	}

	Entity::Entity(std::string p_name)
	:name(p_name)
	{
		SetBaseEntityValues();
	}

	Entity::Entity(std::string p_name, Rect p_rect, SDL_Texture* p_texture)
	:name(p_name), sprite(p_texture), rect(p_rect)
	{
		SetBaseEntityValues();
	}

	Entity::Entity(std::string p_name, Vector2int pos, EntityComponent::TextComponent p_textComponent)
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
			if (textComponent.bgColor == NULL)
				sprite = Resources::TextSprite(textComponent.text, textComponent.font, *textComponent.color);
			else
				sprite = Resources::TextSprite(textComponent.text, textComponent.font, *textComponent.color, *textComponent.bgColor);

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

	void Entity::ReloadSprite()
	{
		/* Destroy the old sprite */
		SDL_DestroyTexture(sprite);

		/* Create new text sprite */
		LoadSprite();
	}
}
