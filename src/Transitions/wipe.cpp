#include "Transitions/Wipe.hpp"
#include "Render.hpp"
#include "Values.hpp"

namespace Birb
{
	namespace Transition
	{
		Wipe::Wipe(const Color& color, Direction direction)
		:direction(direction)
		{
			wipe_rect = Rect(0, 0, 0, 0, color);
		}

		Wipe::~Wipe() {}

		void Wipe::draw(float progress)
		{
			switch (direction)
			{
				case (LEFT):
					wipe_rect.x = Global::RenderVars::WindowDimensions.x - Global::RenderVars::WindowDimensions.x * progress;
					wipe_rect.w = Global::RenderVars::WindowDimensions.x;
					wipe_rect.h = Global::RenderVars::WindowDimensions.y;
					break;

				case (RIGHT):
					wipe_rect.w = Global::RenderVars::WindowDimensions.x * progress;
					wipe_rect.h = Global::RenderVars::WindowDimensions.y;
					break;

				case (UP):
					wipe_rect.y = Global::RenderVars::WindowDimensions.y - Global::RenderVars::WindowDimensions.y * progress;
					wipe_rect.w = Global::RenderVars::WindowDimensions.x;
					wipe_rect.h = Global::RenderVars::WindowDimensions.y;
					break;

				case (DOWN):
					wipe_rect.w = Global::RenderVars::WindowDimensions.x;
					wipe_rect.h = Global::RenderVars::WindowDimensions.y * progress;
					break;
			}

			Render::DrawRect(wipe_rect);
		}

		void Wipe::set_color(const Color& color)
		{
			wipe_rect.color = color;
		}
	}
}
