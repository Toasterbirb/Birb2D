#pragma once

#include <SDL2/SDL.h>
#include "Color.hpp"
#include "Polygon.hpp"
#include "SceneObject.hpp"
#include "Vector.hpp"

namespace Birb
{
	class Rect : public SceneObject
	{
	public:
		Rect();
		Rect(const float& p_x, const float& p_y, const float& p_w, const float& p_h);
		Rect(const float& p_x, const float& p_y, const float& p_w, const float& p_h, const Color& color);

		std::string toString() const;
		Polygon toPolygon() const;
		Rect getInt() const;
		SDL_Rect getSDLRect() const;

		float x, y, w, h;
		Color color;

		bool operator==(const Rect& other) const
		{
			return 	(x == other.x
					&& y == other.y
					&& w == other.w
					&& h == other.h);
		}

	private:
		void RenderFunc() override;
		void SetPos(const Vector2f& delta) override;
	};

	inline std::ostream& operator<<(std::ostream& stream, const Rect& other)
	{
		stream << other.x << ", " << other.y << ", " << other.w << ", " << other.h;
		return stream;
	}
}
