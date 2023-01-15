#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <functional>
#endif

#include "BaseEntity.hpp"

namespace Birb
{
	namespace Entity
	{
		/// Click adds button functionality to the Entity
		class Button : public BaseEntity
		{
		public:
			Button();
			Button(const Rect& rect);
			Button(const std::string& name, const Rect& rect);
			Button(const std::function<void()>& p_onClick);
			bool active;
			bool isPressed;
			std::function<void()> onMouseDown;
			std::function<void()> onClick;
            std::function<void()> onHover;
            std::function<void()> onDrag;
		private:
			void AssignPlaceholderEvents();
			static void PlaceHolderMouseDownEvent();
			static void PlaceHolderClickEvent();
			static void PlaceHolderHoverEvent();
			static void PlaceHolderDragEvent();
		};
	}
}
