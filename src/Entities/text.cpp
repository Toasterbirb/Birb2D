#include "Entities/Text.hpp"
#include "Logger.hpp"
#include "Render.hpp"
#include "Resources.hpp"
#include "Values.hpp"
#include "microprofile.h"

#define PROFILER_GROUP "Entities"
#define PROFILER_COLOR MP_LIGHTGREEN

namespace Birb
{
	namespace Entity
	{
		Text::Text()
		:font(&Global::DefaultSettings::DefaultFont), wrapLength(0), has_background_color(false)
		{
			text 	= "";
			color 	= Colors::White;
			bgColor = Colors::Black;
			wrapLength = 0;
			sprite = Texture();
		}

		Text::~Text()
		{
			sprite.Destroy();
		}

		Text::Text(const std::string& name, const Vector2Int& pos, const std::string& text, Font* font, const Color& color)
		:color(color), text(text), font(font), wrapLength(0), has_background_color(false)
		{
			this->name = name;
			this->rect = pos;
			ReloadSprite();
		}

		Text::Text(const std::string& name, const Vector2Int& pos, const std::string& text, Font* font, const Color& color, const Color& bg_color)
		:color(color), bgColor(bg_color), text(text), font(font), wrapLength(0), has_background_color(true)
		{
			this->name = name;
			this->rect = pos;
			ReloadSprite();
		}

		Text::Text(const std::string& text, const Vector2Int& pos, Font* font, const Color& color)
		:color(color), text(text), font(font), wrapLength(0), has_background_color(false)
		{
			this->rect = pos;
			ReloadSprite();
		}

		Text::Text(const std::string& text, Font* font, const Color& color)
		:color(color), text(text), font(font), has_background_color(false)
		{
			wrapLength = 0;
			ReloadSprite();
		}

		Text::Text(const std::string& text, Font* font, const Color& color, const Color& bg_color)
		:color(color), bgColor(bg_color), text(text), font(font), has_background_color(true)
		{
			wrapLength = 0;
			ReloadSprite();
		}

		void Text::Construct(const std::string& text, const Vector2Int& pos, Font* font, const Color& color)
		{
			/* If this text entity already had some text on it,
			 * we can assume that its sprite has been generated
			 * so we can safely clean it out */
			this->sprite.Destroy();

			this->text = text;
			this->rect = pos;
			this->font = font;
			this->color = color;

			/* Re-create the text sprite and blow the fuse if something
			 * goes wrong */
			if (!LoadSprite())
				BlowErrorFuse();
		}

		std::string Text::GetText() const
		{
			return this->text;
		}

		Color Text::GetColor() const
		{
			return this->color;
		}

		Color Text::GetBgColor() const
		{
			return this->bgColor;
		}

		bool Text::SetText(const std::string& newText)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Set TextComponent text", PROFILER_COLOR);

			/* Don't do anything if the text hasn't changed at all */
			if (text == newText)
				return true;

			text = newText;
			return ReloadSprite();
		}

		void Text::SetFont(Font* font)
		{
			/* Don't do anything if the font hasn't changed at all */
			if (&this->font == &font)
				return;

			this->font = font;
			ReloadSprite();
		}

		void Text::SetTextColor(const Color& color)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Set entity text color", PROFILER_COLOR);

			/* Don't do anything if the color hasn't changed at all */
			if (this->color.a == color.a
				&& this->color.r == color.r
				&& this->color.g == color.g
				&& this->color.b == color.b) return;

			this->color = color;
			ReloadSprite();
		}

		void Text::SetTextBgColor(const Color& color)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Set entity background text color", PROFILER_COLOR);

			/* Don't do anything if the color hasn't changed at all */
			if (this->bgColor.a == color.a
				&& this->bgColor.r == color.r
				&& this->bgColor.g == color.g
				&& this->bgColor.b == color.b) return;

			this->bgColor = color;
			ReloadSprite();
		}

		Vector2Int Text::sprite_dimensions() const
		{
			return sprite.dimensions();
		}

		bool Text::ReloadSprite()
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Reload sprite", PROFILER_COLOR);

			/* If the new text would be empty, simply disable the text entity. If the
			 * entity then gets some actual text, toggle the entity back on and set the
			 * text */
			if (text.empty())
			{
				this->active = false;
				this->rect.w = 0;
				return true;
			}
			else
			{
				this->active = true;
			}


			/* Destroy the old sprite */
			if (sprite.isLoaded())
				sprite.Destroy();

			bool result = LoadSprite();

			/* Check if everything is okay with the sprite */
			if (sprite.ErrorFuseStatus() || !result)
				BlowErrorFuse();

			/* Create new text sprite */
			return result;
		}

		bool Text::LoadSprite()
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Load sprite", PROFILER_COLOR);

			/* Generate the sprite if there's text to render */
			if (text != "")
			{
				if (!has_background_color)
					sprite = Resources::TextSprite(text, *font, color, wrapLength);
				else
					sprite = Resources::TextSprite(text, *font, color, bgColor);

				if (sprite.isLoaded() == false)
				{
					Debug::Log("Something went wrong while creating the text sprite for '" + name + "'", Debug::error);
					BlowErrorFuse();
					return false;
				}
				else
				{
					/* Get sprite scale automatically */
					rect.w = sprite.dimensions().x;
					rect.h = sprite.dimensions().y;
				}
			}

			return true;
		}

		void Text::RenderFunc()
		{
			Render::DrawTexture(sprite, rect, world_space, angle);
		}

		void Text::SetPos(const Vector2& delta)
		{
			rect.x += delta.x;
			rect.y += delta.y;
		}
	}
}
