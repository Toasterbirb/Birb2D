#include "EntityComponent/Text.hpp"

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
	}
}
