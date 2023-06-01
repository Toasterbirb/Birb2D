#pragma once

#include "Color.hpp"
#include "Rect.hpp"
#include "Transition.hpp"

namespace Birb
{
	namespace Transition
	{
		class Fade : public BaseTransition
		{
		public:
			Fade(const Color& color);
			virtual ~Fade();

			void draw(float progress);
			void set_color(const Color& color);

		private:
			Rect fade_rect;
		};
	}
}
