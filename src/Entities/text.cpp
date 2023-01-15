#include "Entities/Text.hpp"
#include "microprofile.h"
#include "Resources.hpp"
#include "Logger.hpp"
#include "Values.hpp"

#define PROFILER_GROUP "Entities"
#define PROFILER_COLOR MP_LIGHTGREEN

namespace Birb
{
	namespace Entity
	{
		Text::Text()
		:font(Global::DefaultSettings::DefaultFont)
		{
			text 	= "";
			color 	= Colors::White;
			bgColor = NULL;
			wrapLength = 0;
		}

		Text::Text(const std::string& text, Font& font, const Color& color)
		:color(color), text(text), font(font)
		{
			bgColor = NULL;
			wrapLength = 0;
		}

		Text::Text(const std::string& text, Font& font, const Color& color, const Color& bgColor)
		:color(color), bgColor(bgColor), text(text), font(font)
		{
			wrapLength = 0;
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

		void Text::SetFont(Font& font)
		{
			/* Don't do anything if the font hasn't changed at all */
			if (&this->font == &font)
				return;

			this->font = font;
			ReloadSprite();
		}

		void Text::SetTextColor(Color& color)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Set entity TextComponent color", PROFILER_COLOR);

			/* Don't do anything if the color hasn't changed at all */
			if (this->color.a == color.a
				&& this->color.r == color.r
				&& this->color.g == color.g
				&& this->color.b == color.b) return;

			this->color = color;
			ReloadSprite();
		}

		bool Text::ReloadSprite()
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Reload sprite", PROFILER_COLOR);

			/* Destroy the old sprite */
			texture.Destroy();

			/* Create new text sprite */
			return LoadSprite();
		}

		bool Text::LoadSprite()
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Load sprite", PROFILER_COLOR);

			/* Generate the texture if there's text to render */
			if (text != "")
			{
				if (bgColor == NULL)
					texture = Resources::TextSprite(text, font, color, wrapLength);
				else
					texture = Resources::TextSprite(text, font, color, bgColor);

				if (texture.isLoaded() == false)
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
	}
}
