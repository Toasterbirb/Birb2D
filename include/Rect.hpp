#pragma once

#include <SDL2/SDL.h>
#include "Vector.hpp"

namespace Birb
{
	struct Rect
	{
		Rect();
		Rect(const float& p_x, const float& p_y, const float& p_w, const float& p_h);

		std::string toString();
		Vector2f* toPolygon();
		Rect getInt();
		SDL_Rect getSDLRect() const;

		float x, y, w, h;

		bool operator==(const Rect& other) const
		{
			return 	(x == other.x
					&& y == other.y
					&& w == other.w
					&& h == other.h);
		}
	};
}
