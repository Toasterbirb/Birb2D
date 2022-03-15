#include "Rect.hpp"
#include "Renderwindow.hpp"
#include "Utils.hpp"

namespace Birb
{
	Rect::Rect()
	:x(0.0f), y(0.0f), w(0.0f), h(0.0f)
	{
		color = Color(0xFFFFFF);
	}

	Rect::Rect(const float& p_x, const float& p_y, const float& p_w, const float& p_h)
	:x(p_x), y(p_y), w(p_w), h(p_h)
	{
		color = Color(0xFFFFFF);
	}

	Rect::Rect(const float& p_x, const float& p_y, const float& p_w, const float& p_h, const Color& color)
	:x(p_x), y(p_y), w(p_w), h(p_h), color(color)
	{}

	std::string Rect::toString()
	{
		return utils::CleanDecimals(x) + ", " +
			utils::CleanDecimals(y) + ", " +
			utils::CleanDecimals(w) + ", " +
			utils::CleanDecimals(h);
	}

	Vector2f* Rect::toPolygon()
	{
		Vector2f* points = new Vector2f[4] {
			Vector2f(x, y),
			Vector2f(x + w, y),
			Vector2f(x + w, y + h),
			Vector2f(x, y + h)
		};

		return points;
	}

	Rect Rect::getInt()
	{
		Rect roundedRect;
		roundedRect.x = round(x);
		roundedRect.y = round(y);
		roundedRect.w = round(w);
		roundedRect.h = round(h);

		return roundedRect;
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
}
