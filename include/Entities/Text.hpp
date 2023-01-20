#pragma once

#include "Font.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include "BaseEntity.hpp"
#include "Vector/Vector2Int.hpp"

namespace Birb
{
	namespace Entity
	{
		/// Text contains details needed to generate a sprite for the Entity in case the Entity is used to display text.
		class Text : public BaseEntity, public SceneObject
		{
		public:
			Text();
			virtual ~Text();

			/// This is here just for legacy compatibilitys sake
			Text(const std::string& name, const Vector2Int& pos, const std::string& text, Font* font, const Color& color);

			/// This is here just for legacy compatibilitys sake
			Text(const std::string& name, const Vector2Int& pos, const std::string& text, Font* font, const Color& color, const Color& bg_color);

			Text(const std::string& text, const Vector2Int& pos, Font* font, const Color& color);
			Text(const std::string& text, Font* font, const Color& color);
			Text(const std::string& text, Font* font, const Color& color, const Color& bg_color);

			void Construct(const std::string& text, const Vector2Int& pos, Font* font, const Color& color);

			Color color; 	///< Surface color of the text
			Color bgColor; ///< Background color for the text component

			/* FIXME: Create a constructor for this variable */
			int wrapLength;

			std::string GetText() const;
			Color GetColor() const;
			Color GetBgColor() const;

			bool SetText(const std::string& newText); 	///< Change the text in Text and reload the sprite
			void SetFont(Font* font); 			///< Change the font in Text and reload the sprite
			void SetTextColor(Color& color); 			///< Change the color in Text and reload the sprite

			Vector2Int sprite_dimensions() const;

			Text& operator=(const Text& other)
			{
				/* Base entity stuff */
				this->name 		= other.name;
				this->angle 	= other.angle;
				this->rect 		= other.rect;

				/* SceneObject stuff */
				this->renderingPriority 	= other.renderingPriority;
				this->active 				= other.active;
				this->parallax_multiplier 	= other.parallax_multiplier;
				this->world_space 			= other.world_space;

				this->text 		= other.text;
				this->font 		= other.font;
				this->color 	= other.color;
				this->bgColor 	= other.bgColor;

				this->has_background_color 	= other.has_background_color;

				/* Reload the sprite using the new information */
				if (!this->ReloadSprite())
					this->BlowErrorFuse();

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
			Font* font;
			bool has_background_color;

			void RenderFunc() override;
			void SetPos(const Vector2& delta) override;
		};
	}
}
