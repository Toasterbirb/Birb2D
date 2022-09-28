#include "Diagnostics.hpp"
#include "Entity.hpp"
#include "Logger.hpp"
#include "Renderwindow.hpp"
#include "Values.hpp"

namespace Birb
{
	namespace EntityComponent
	{
		Text::Text()
		{
			text 	= "";
			font 	= NULL;
			color 	= NULL;
			bgColor = NULL;
			wrapLength = 0;
		}

		Text::Text(const std::string& text, Font* font, Color* color)
		:text(text), font(font), color(color)
		{
			bgColor = NULL;
			wrapLength = 0;
		}

		Text::Text(const std::string& text, Font* font, Color* color, Color* bgColor)
		:text(text), font(font), color(color), bgColor(bgColor)
		{
			wrapLength = 0;
		}

		void PlaceHolderMouseDownEvent()
		{
#ifdef DEBUG
			if (Diagnostics::Debugging::Buttons)
				Debug::Log("Placeholder onMouseDown event");
#endif
		}

		void PlaceHolderClickEvent()
		{
#ifdef DEBUG
            if (Diagnostics::Debugging::Buttons)
                Debug::Log("Placeholder onClick event");
#endif
		}

        void PlaceHolderHoverEvent()
        {
#ifdef DEBUG
            if (Diagnostics::Debugging::Buttons)
                Debug::Log("Placeholder onHover event");
#endif
        }

        void PlaceHolderDragEvent()
        {
#ifdef DEBUG
            if (Diagnostics::Debugging::Buttons)
                Debug::Log("Placeholder onDrag event");
#endif
        }

		void Click::AssignPlaceholderEvents()
		{
			onMouseDown = PlaceHolderMouseDownEvent;
            onHover = PlaceHolderHoverEvent;
            onDrag  = PlaceHolderDragEvent;
		}

		Click::Click()
		{
			AssignPlaceholderEvents();
			onClick = PlaceHolderClickEvent;
			active = true;
		}

		Click::Click(const std::function<void()>& p_onClick)
		:onClick(p_onClick)
		{
			AssignPlaceholderEvents();
			active = true;
		}

		Animation::Animation()
		{
			fps 			= 24;
			loop 			= false;
			frameIndex 		= 0;
			frameCount 		= 0;
			spriteSize 		= { 16, 16 };
			animationQueued = false;
		}

		Animation::Animation(const Vector2int& p_spriteSize, const int& p_frameCount, const int& p_fps)
		:spriteSize(p_spriteSize), frameCount(p_frameCount), fps(p_fps), lastFrame(p_frameCount - 1)
		{
			frameIndex 		= 0;
			loop 			= false;
			animationQueued = false;
		}

		Animation::Animation(const Vector2int& p_spriteSize, const int& p_frameCount, const int& p_fps, const bool& p_loop)
		:spriteSize(p_spriteSize), frameCount(p_frameCount), fps(p_fps), loop(p_loop), lastFrame(p_frameCount - 1)
		{
			frameIndex 		= 0;
			animationQueued = false;
		}


		void Animation::ResetAnimationAtlas()
		{
			frameIndex = 0;
			lastFrame = frameCount - 1;
		}

		void Animation::StartAnimation()
		{
			ResetAnimationAtlas();
			animationQueued = true;
		}

		void Animation::StartAnimation(const int& p_startFrame)
		{
			frameIndex = p_startFrame;
			lastFrame = frameCount - 1;
			animationQueued = true;
		}

		void Animation::StartAnimation(const int& p_startFrame, const int& p_lastFrame)
		{
			frameIndex = p_startFrame;
			lastFrame = p_lastFrame;
			animationQueued = true;
		}

		ProgressBar::ProgressBar()
		{
			borderWidth 	= 1;
			borderColor 	= &Birb::Colors::White;
			backgroundColor = &Birb::Colors::Black;
			fillColor 		= &Birb::Colors::White;

			minValue = 0;
			maxValue = 1;
			value = 0;

			active = false;
		}

		ProgressBar::ProgressBar(const int& p_borderWidth, Color* p_borderColor, Color* p_backgroundColor, Color* p_fillColor)
		:borderWidth(p_borderWidth), borderColor(p_borderColor), backgroundColor(p_backgroundColor), fillColor(p_fillColor)
		{
			minValue = 0;
			maxValue = 1;
			value = 0.25f;

			active = true;
		}

		ProgressBar::ProgressBar(const int& p_borderWidth, Color* p_borderColor, Color* p_backgroundColor, Color* p_fillColor, const int& p_minValue, const int& p_maxValue, const int& p_value)
		:borderWidth(p_borderWidth), borderColor(p_borderColor), backgroundColor(p_backgroundColor), fillColor(p_fillColor), minValue(p_minValue), maxValue(p_maxValue), value(p_value)
		{
			active = true;
		}
	}

	Vector2int Entity::getAtlasPosition(const int& frame)
	{
		Vector2int pos;
		int index = frame;

		int texWidth;
		//int texHeight;
		texWidth = sprite.dimensions().x;
		//texHeight = sprite.dimensions().y;

		int spritesPerRow = texWidth / animationComponent.spriteSize.x;
		float fullRowCount = std::floor(index / spritesPerRow);
		float leftOver = ((index / (float)spritesPerRow) - fullRowCount) * spritesPerRow;

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
		localScale = Vector2f(1, 1);
		active = true;
	}

	void Entity::CenterRelativeTo(const Rect& rect)
	{
		Vector2int textureDimensions = sprite.dimensions();
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

	Entity::Entity(const std::string& name, const Vector2int& pos, Texture texture)
	:name(name), sprite(texture)
	{
		SetBaseEntityValues();
		rect.x = pos.x;
		rect.y = pos.y;

		/* Get texture scale automatically */
		rect.w = texture.dimensions().x;
		rect.h = texture.dimensions().y;
	}

	Entity::Entity(const std::string& name, const Vector2int& pos, Texture texture, const EntityComponent::Animation& animationComponent)
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

	Entity::Entity(const std::string& p_name, const Vector2int& pos, const EntityComponent::Text& p_textComponent)
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

	void Entity::SetPos(const Vector2f& delta)
	{
		rect.x += delta.x;
		rect.y += delta.y;
	}
}
