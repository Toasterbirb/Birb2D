#include "Entities/Button.hpp"
#include "Diagnostics.hpp"

namespace Birb
{
	namespace Entity
	{
		Button::Button()
		{
			AssignPlaceholderEvents();
			onClick 	= PlaceHolderClickEvent;
			active 		= true;
			isPressed 	= false;
		}

		Button::Button(const Rect& rect)
		:active(true), isPressed(false)
		{
			AssignPlaceholderEvents();
			this->rect = rect;
		}

		Button::Button(const std::string& name, const Rect& rect)
		:active(true), isPressed(false)
		{
			this->rect = rect;
			this->name = name;
		}

		Button::Button(const std::function<void()>& p_onClick)
		:onClick(p_onClick)
		{
			AssignPlaceholderEvents();
			active 		= true;
			isPressed 	= false;
		}

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

		void Button::RenderFunc()
		{
			Render::DrawRect(rect);
		}

		void Button::SetPos(const Vector2& delta)
		{
			rect.x += delta.x;
			rect.y += delta.y;
		}

	}
}
