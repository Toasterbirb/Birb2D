#include "Polygon.hpp"
#include "Rect.hpp"
#include "Render.hpp"
#include "Utils.hpp"

#ifdef DISTCC
#include <iostream>
#endif

namespace Birb
{
	Rect::Rect()
	:x(0.0f), y(0.0f), w(0.0f), h(0.0f)
	{
		color = Color(255, 255, 255);
	}

	Rect::Rect(const float& p_x, const float& p_y, const float& p_w, const float& p_h)
	:x(p_x), y(p_y), w(p_w), h(p_h)
	{
		color = Color(255, 255, 255);
	}

	Rect::Rect(const float& p_x, const float& p_y, const float& p_w, const float& p_h, const Color& color)
	:x(p_x), y(p_y), w(p_w), h(p_h), color(color)
	{}

	std::string Rect::toString() const
	{
		return utils::CleanDecimals(x) + ", " +
			utils::CleanDecimals(y) + ", " +
			utils::CleanDecimals(w) + ", " +
			utils::CleanDecimals(h);
	}

	Polygon Rect::toPolygon() const
	{
		Vector2 points[4] = {
			Vector2(x, y),
			Vector2(x + w, y),
			Vector2(x + w, y + h),
			Vector2(x, y + h)
		};

		return Polygon(points, 4);
	}

	std::vector<Line> Rect::toLines() const
	{
		std::vector<Line> lines(4);
		lines[0] = (Line({ x, 		y 	}, 		{ x + w, 	y }));
		lines[1] = (Line({ x + w, 	y 	}, 		{ x + w, 	y + h }));
		lines[2] = (Line({ x + w, 	y + h }, 	{ x, 		y + h }));
		lines[3] = (Line({ x, 		y + h }, 	{ x, 		y }));
		return lines;
	}

	Rect Rect::getInt() const
	{
		Rect roundedRect;
		roundedRect.x = round(x);
		roundedRect.y = round(y);
		roundedRect.w = round(w);
		roundedRect.h = round(h);

		return roundedRect;
	}

	Vector2 Rect::centerPoint() const
	{
		return {x + w / 2, y + h / 2};
	}

	SDL_Rect Rect::getSDLRect() const
	{
		SDL_Rect sdlrect;
		sdlrect.h = h;
		sdlrect.w = w;
		sdlrect.x = x;
		sdlrect.y = y;
		return sdlrect;
	}

	void Rect::RenderFunc()
	{
		Render::DrawRect(color, *this);
	}

	void Rect::SetPos(const Vector2& delta)
	{
		x += delta.x;
		y += delta.y;
	}

	std::ostream& operator<<(std::ostream& stream, const Rect& other)
	{
		stream << other.x << ", " << other.y << ", " << other.w << ", " << other.h;
		return stream;
	}
}
