#pragma once
#include "Color.hpp"

namespace Birb
{
	namespace Transition
	{
		enum Direction
		{
			LEFT, RIGHT, UP, DOWN
		};

	}

	/// Base class for transitions. Not meant to be used by itself
	class BaseTransition
	{
	public:
		BaseTransition();
		virtual ~BaseTransition();

		/* Render the transition with the progress being a value between 0 and 1 */
		virtual void draw(float progress)   = 0;
		virtual void set_color(const Color& color) = 0;
	};
}
