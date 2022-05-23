#include "Window.hpp"
#include "Render.hpp"
#include "Values.hpp"
#include "Logger.hpp"
#include "Diagnostics.hpp"


namespace Birb
{
	Window::~Window()
	{
		Cleanup();
	}

	bool Window::CursorInRect(const Rect& rect) const
	{
		Vector2int cursorPos = CursorPosition();

		if (cursorPos.x > rect.x && cursorPos.x < rect.x + rect.w)
			if (cursorPos.y > rect.y && cursorPos.y < rect.y + rect.h)
				return true;

		return false;
	}


	Vector2f Window::window_dimensions_multiplier()
	{
		return Vector2f((float)dimensions.x / (float)original_window_dimensions.x,
						(float)dimensions.y / (float)original_window_dimensions.y);
	}




}
