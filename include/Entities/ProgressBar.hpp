#pragma once

#include "Color.hpp"
#include "BaseEntity.hpp"

namespace Birb
{
	struct Vector2;

	namespace Entity
	{
		/// ProgressBar is used to create... well... progress bars
		/// If the entity has a sprite on it. That will be used instead of the fill color
		class ProgressBar : public BaseEntity, public SceneObject
		{
		public:
			ProgressBar();
			ProgressBar(int border_width, const Color& border_color, const Color& background_color, const Color& fill_color);
			ProgressBar(int border_width, const Color& border_color, const Color& background_color, const Color& fill_color, int min_value, int max_value, int value);

			int borderWidth; ///< Sets the thickness of the borders around the progress bar
			Color borderColor; ///< Border color around the fill area
			Color backgroundColor; ///< Background color that is below the filled area
			Color fillColor; ///< Color that hides the background color

			float minValue; ///< Value where the progress bar should be empty
			float maxValue; ///< Value where the progress bar should be full
			float value; ///< Current progress value

			/// Set the value so that the fill bar would reach the
			/// given point. Nothing will happen if the point given
			/// is outside of the Entity surface area
			void SetValueFromRelativePoint(Vector2 point);

			bool operator==(const ProgressBar& other) const
			{
				return 	(borderWidth 		== other.borderWidth
						&& borderColor 		== other.borderColor
						&& backgroundColor 	== other.backgroundColor
						&& fillColor 		== other.fillColor
						&& minValue 		== other.minValue
						&& maxValue 		== other.maxValue);
			}

		private:
			void RenderFunc() override;
			void SetPos(const Vector2& delta) override;
		};
	}
}
