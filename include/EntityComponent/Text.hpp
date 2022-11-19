#pragma once

#include "Font.hpp"
#include "Color.hpp"

namespace Birb
{
	namespace EntityComponent
	{
		/// Text contains details needed to generate a sprite for the Entity in case the Entity is used to display text.
		struct Text
		{
			Text();
			Text(const std::string& text, Font* font, Color* color);
			Text(const std::string& text, Font* font, Color* color, Color* bgColor);

			/* FIXME: figure out how to make these variables private */
			std::string text;
			Font* font;
			Color* color; 	///< Surface color of the text
			Color* bgColor; ///< Background color for the text component

			/* FIXME: Create a constructor for this variable */
			int wrapLength;

			bool operator==(const Text& other) const
			{
				return 	(text 		== other.text
						&& &font 	== &other.font
						&& color 	== other.color
						&& bgColor 	== other.bgColor);
			}
		};
	}
}
