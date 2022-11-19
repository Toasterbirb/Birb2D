#include "EntityComponent/Click.hpp"
#include "Diagnostics.hpp"

namespace Birb
{
	namespace EntityComponent
	{
		void Click::PlaceHolderMouseDownEvent()
		{
#ifdef DEBUG
			if (Diagnostics::Debugging::Buttons)
				Debug::Log("Placeholder onMouseDown event");
#endif
			return;
		}

		void Click::PlaceHolderClickEvent()
		{
#ifdef DEBUG
            if (Diagnostics::Debugging::Buttons)
                Debug::Log("Placeholder onClick event");
#endif
			return;
		}

        void Click::PlaceHolderHoverEvent()
        {
#ifdef DEBUG
            if (Diagnostics::Debugging::Buttons)
                Debug::Log("Placeholder onHover event");
#endif
			return;
        }

        void Click::PlaceHolderDragEvent()
        {
#ifdef DEBUG
            if (Diagnostics::Debugging::Buttons)
                Debug::Log("Placeholder onDrag event");
#endif
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
