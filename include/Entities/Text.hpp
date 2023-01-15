#pragma once

#include "Font.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include "BaseEntity.hpp"

namespace Birb
{
	namespace Entity
	{
		/// Text contains details needed to generate a sprite for the Entity in case the Entity is used to display text.
		class Text : public BaseEntity
		{
		public:
			Text();
			Text(const std::string& text, Font& font, const Color& color);
			Text(const std::string& text, Font& font, const Color& color, const Color& bgColor);

			Color color; 	///< Surface color of the text
			Color bgColor; ///< Background color for the text component

			/* FIXME: Create a constructor for this variable */
			int wrapLength;

			bool SetText(const std::string& newText); 	///< Change the text in Text and reload the sprite
			void SetFont(Font& font); 			///< Change the font in Text and reload the sprite
			void SetTextColor(Color& color); 			///< Change the color in Text and reload the sprite

			Text& operator=(const Text& other)
			{
				this->sprite 	= other.sprite;
				this->text 		= other.text;
				this->font 		= other.font;
				this->color 	= other.color;
				this->bgColor 	= other.bgColor;
				return *this;
			}
			//SceneObject& operator=(SceneObject&&) 		= default;

			bool operator==(const Text& other) const
			{
				return 	(text 		== other.text
						&& &font 	== &other.font
						&& color 	== other.color
						&& bgColor 	== other.bgColor);
			}

		private:
			bool ReloadSprite();
			bool LoadSprite();
			Texture sprite;
			std::string text;
			Font& font;

			void RenderFunc() override;
		};
	}
}
