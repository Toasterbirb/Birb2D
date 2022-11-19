#include "EntityComponent/ProgressBar.hpp"

namespace Birb
{
	namespace EntityComponent
	{
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
}
