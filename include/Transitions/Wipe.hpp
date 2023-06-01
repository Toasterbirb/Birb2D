#pragma once

#include "Color.hpp"
#include "Rect.hpp"
#include "Transition.hpp"

namespace Birb
{
	namespace Transition
	{
		class Wipe : public BaseTransition
		{
		public:
			Wipe(const Color& color, Direction direction);
			virtual ~Wipe();

			void draw(float progress);
			void set_color(const Color& color);

		private:
			Rect wipe_rect;
			Direction direction;
		};
	}
}
