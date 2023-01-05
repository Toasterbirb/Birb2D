#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <functional>
#endif

namespace Birb
{
	namespace EntityComponent
	{
		/// Click adds button functionality to the Entity
		class Click
		{
		public:
			Click();
			Click(const std::function<void()>& p_onClick);
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
