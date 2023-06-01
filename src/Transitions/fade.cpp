#include "Transitions/Fade.hpp"
#include "Render.hpp"
#include "Values.hpp"
#include <cassert>

namespace Birb
{
	namespace Transition
	{
		Fade::Fade(const Color& color)
		{
			fade_rect = Rect(
				0,
				0,
				Global::RenderVars::WindowDimensions.x,
				Global::RenderVars::WindowDimensions.y,
				color
			);
		}

		Fade::~Fade()
		{}

		void Fade::draw(float progress)
		{
			/* Make sure that the window dimensions are kept up-to-date */
			fade_rect.w = Global::RenderVars::WindowDimensions.x;
			fade_rect.h = Global::RenderVars::WindowDimensions.y;

			fade_rect.color.a = progress * 255.0f;
			Render::DrawRect(fade_rect);
		}

		void Fade::set_color(const Color& color)
		{
			fade_rect.color = color;
		}
	}
}
