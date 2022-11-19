#pragma once

#include "Color.hpp"

namespace Birb
{
	namespace EntityComponent
	{
		/// ProgressBar is used to create... well... progress bars
		/// If the entity has a sprite on it. That will be used instead of the fill color
		struct ProgressBar
		{
			ProgressBar();
			ProgressBar(const int& p_borderWidth, Color* p_borderColor, Color* p_backgroundColor, Color* p_fillColor);
			ProgressBar(const int& p_borderWidth, Color* p_borderColor, Color* p_backgroundColor, Color* p_fillColor, const int& p_minValue, const int& p_maxValue, const int& p_value);
			bool active; ///< Setting this value active toggles on the progress bar component

			int borderWidth; ///< Sets the thickness of the borders around the progress bar
			Color* borderColor; ///< Border color around the fill area
			Color* backgroundColor; ///< Background color that is below the filled area
			Color* fillColor; ///< Color that hides the background color

			float minValue; ///< Value where the progress bar should be empty
			float maxValue; ///< Value where the progress bar should be full
			float value; ///< Current progress value

			bool operator==(const ProgressBar& other) const
			{
				return 	(borderWidth 		== other.borderWidth
						&& borderColor 		== other.borderColor
						&& backgroundColor 	== other.backgroundColor
						&& fillColor 		== other.fillColor
						&& minValue 		== other.minValue
						&& maxValue 		== other.maxValue);
			}
		};
	}
}
