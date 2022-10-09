#include "Rect.hpp"
#include "Renderwindow.hpp"
#include "Utils.hpp"

namespace Birb
{
	Rect::Rect()
	:x(0.0f), y(0.0f), w(0.0f), h(0.0f)
	{
		color = &Colors::White;
	}

	Rect::Rect(const float& p_x, const float& p_y, const float& p_w, const float& p_h)
	:x(p_x), y(p_y), w(p_w), h(p_h)
	{
		color = &Colors::White;
	}

	Rect::Rect(const float& p_x, const float& p_y, const float& p_w, const float& p_h, Color& color)
	:x(p_x), y(p_y), w(p_w), h(p_h), color(&color)
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
		Render::DrawRect(*color, *this);
	}

	void Rect::SetPos(const Vector2& delta)
	{
		x += delta.x;
		y += delta.y;
	}
}
