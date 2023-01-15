#include "Entities/Button.hpp"
#include "Diagnostics.hpp"

namespace Birb
{
	namespace EntityComponent
	{
		void Button::PlaceHolderMouseDownEvent()
		{
			if (Diagnostics::Debugging::Buttons)
				Debug::Log("Placeholder onMouseDown event");

			return;
		}

		void Button::PlaceHolderClickEvent()
		{
            if (Diagnostics::Debugging::Buttons)
                Debug::Log("Placeholder onClick event");

			return;
		}

        void Button::PlaceHolderHoverEvent()
        {
            if (Diagnostics::Debugging::Buttons)
                Debug::Log("Placeholder onHover event");

			return;
        }

        void Button::PlaceHolderDragEvent()
        {
            if (Diagnostics::Debugging::Buttons)
                Debug::Log("Placeholder onDrag event");

			return;
        }

		void Button::AssignPlaceholderEvents()
		{
			onMouseDown = PlaceHolderMouseDownEvent;
            onHover = PlaceHolderHoverEvent;
            onDrag  = PlaceHolderDragEvent;
		}

		Button::Button()
		{
			AssignPlaceholderEvents();
			onClick 	= PlaceHolderClickEvent;
			active 		= true;
			isPressed 	= false;
		}

		Button::Button(const std::function<void()>& p_onClick)
		:onClick(p_onClick)
		{
			AssignPlaceholderEvents();
			active 		= true;
			isPressed 	= false;
		}
	}
}
