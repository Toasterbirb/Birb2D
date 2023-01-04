#include "Entity.hpp"
#include "EntityComponent/ProgressBar.hpp"
#include "Logger.hpp"
#include "Physics.hpp"
#include "Vector/Vector2.hpp"

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
			parent_entity = nullptr;
		}

		ProgressBar::ProgressBar(const int& p_borderWidth, Color* p_borderColor, Color* p_backgroundColor, Color* p_fillColor)
		:borderWidth(p_borderWidth), borderColor(p_borderColor), backgroundColor(p_backgroundColor), fillColor(p_fillColor)
		{
			minValue = 0;
			maxValue = 1;
			value = 0.25f;

			active = true;
			parent_entity = nullptr;
		}

		ProgressBar::ProgressBar(const int& p_borderWidth, Color* p_borderColor, Color* p_backgroundColor, Color* p_fillColor, const int& p_minValue, const int& p_maxValue, const int& p_value)
		:borderWidth(p_borderWidth), borderColor(p_borderColor), backgroundColor(p_backgroundColor), fillColor(p_fillColor), minValue(p_minValue), maxValue(p_maxValue), value(p_value)
		{
			active = true;
			parent_entity = nullptr;
		}

		void ProgressBar::SetValueFromRelativePoint(Vector2 point)
		{
			/* Check if the parent entity has been set */
			// FIXME: Add a more elegant way to make th progressbars aware of their parent entity
			if (parent_entity == nullptr)
			{
				Debug::Log("Set the slider parent entity first before using SetValueFromRelativePoint()", Debug::fixme);
				return;
			}

			/* First test if the point is even on the Entity */
			if (!Physics::PointInRect(parent_entity->rect, point))
				return;

			value = ((point.x - parent_entity->rect.x) / parent_entity->rect.w) * maxValue;
		}
	}
}
