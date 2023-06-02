#include "Entities/ProgressBar.hpp"
#include "Logger.hpp"
#include "Physics.hpp"
#include "Render.hpp"
#include "Vector/Vector2.hpp"

namespace Birb
{
	namespace Entity
	{
		ProgressBar::ProgressBar()
		{
			borderWidth 	= 1;
			borderColor 	= Birb::Colors::White;
			backgroundColor = Birb::Colors::Black;
			fillColor 		= Birb::Colors::White;

			minValue = 0;
			maxValue = 1;
			value = 0;
		}

		ProgressBar::ProgressBar(int border_width, const Color& border_color, const Color& background_color, const Color& fill_color)
		:borderWidth(border_width), borderColor(border_color), backgroundColor(background_color), fillColor(fill_color)
		{
			minValue = 0;
			maxValue = 1;
			value = 0.25f;
		}

		ProgressBar::ProgressBar(int border_width, const Color& border_color, const Color& background_color, const Color& fill_color, int min_value, int max_value, int value)
		:borderWidth(border_width), borderColor(border_color), backgroundColor(background_color), fillColor(fill_color), minValue(min_value), maxValue(max_value), value(value)
		{
			assert(min_value < max_value);
		}

		void ProgressBar::SetValueFromRelativePoint(Vector2 point)
		{
			/* First test if the point is even on the Entity */
			if (!Physics::PointInRect(rect, point))
				return;

			assert(rect.w != 0 && "Zero division");
			value = ((point.x - rect.x) / rect.w) * maxValue;
		}

		void ProgressBar::RenderFunc()
		{
			/* Draw progress bar background unless the bar is full */
			if (value < maxValue)
				Render::DrawRect(backgroundColor, rect);

			/* Draw the progress bar filler box */
			Birb::Rect fillRect(rect.x, rect.y, (value / maxValue) * rect.w, rect.h);
			Render::DrawRect(fillColor, fillRect);

			/* Draw the progress bar outer box */
			Render::DrawRect(borderColor, rect, borderWidth);
		}

		void ProgressBar::SetPos(const Vector2& delta)
		{
			rect.x += delta.x;
			rect.y += delta.y;
		}
	}
}
