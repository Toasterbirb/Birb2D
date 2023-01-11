#include "EntityComponent/Click.hpp"
#include "Diagnostics.hpp"

namespace Birb
{
	namespace EntityComponent
	{
		void Click::PlaceHolderMouseDownEvent()
		{
			if (Diagnostics::Debugging::Buttons)
				Debug::Log("Placeholder onMouseDown event");

			return;
		}

		void Click::PlaceHolderClickEvent()
		{
            if (Diagnostics::Debugging::Buttons)
                Debug::Log("Placeholder onClick event");

			return;
		}

        void Click::PlaceHolderHoverEvent()
        {
            if (Diagnostics::Debugging::Buttons)
                Debug::Log("Placeholder onHover event");

			return;
        }

        void Click::PlaceHolderDragEvent()
        {
            if (Diagnostics::Debugging::Buttons)
                Debug::Log("Placeholder onDrag event");

			return;
        }

		void Click::AssignPlaceholderEvents()
		{
			onMouseDown = PlaceHolderMouseDownEvent;
            onHover = PlaceHolderHoverEvent;
            onDrag  = PlaceHolderDragEvent;
		}

		Click::Click()
		{
			AssignPlaceholderEvents();
			onClick 	= PlaceHolderClickEvent;
			active 		= true;
			isPressed 	= false;
		}

		Click::Click(const std::function<void()>& p_onClick)
		:onClick(p_onClick)
		{
			AssignPlaceholderEvents();
			active 		= true;
			isPressed 	= false;
		}
	}
}
