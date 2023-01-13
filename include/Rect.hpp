#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <iosfwd>
#include <vector>
#include <string>
#endif

#include "Color.hpp"
#include "Line.hpp"
#include "SceneObject.hpp"
#include "Vector/Vector2.hpp"
#include "Vector/Vector2Int.hpp"
#include "Vector/Vector3.hpp"
#include "Vector/Vector3Int.hpp"

namespace Birb
{
	class Polygon;

	class Rect : public SceneObject
	{
	public:
		constexpr Rect()
		:x(0.0f), y(0.0f), w(0.0f), h(0.0f), color(Color(255, 255, 255)) {}

		constexpr Rect(const float& p_x, const float& p_y, const float& p_w, const float& p_h)
		:x(p_x), y(p_y), w(p_w), h(p_h), color(Color(255, 255, 255)) {}

		constexpr Rect(const float& p_x, const float& p_y, const float& p_w, const float& p_h, const Color& color)
		:x(p_x), y(p_y), w(p_w), h(p_h), color(color) {}

		std::string toString() const;
		Polygon toPolygon() const;
		std::vector<Line> toLines() const; ///< Returns the four sides of the rect as lines
		Rect getInt() const;
		Vector2 centerPoint() const;

		SDL_Rect getSDLRect() const;

		float x, y, w, h;
		Color color;

		constexpr bool operator==(const Rect& other) const
		{
			return 	(x == other.x
					&& y == other.y
					&& w == other.w
					&& h == other.h);
		}

		constexpr bool operator!=(const Rect& other) const
		{
			return 	(x != other.x
					|| y != other.y
					|| w != other.w
					|| h != other.h);
		}

		constexpr Rect& operator=(const Vector2& other)
		{
			this->x = other.x;
			this->y = other.y;
			return *this;
		}

		constexpr Rect& operator=(const Vector2Int& other)
		{
			this->x = other.x;
			this->y = other.y;
			return *this;
		}

		constexpr Rect& operator=(const Vector3& other)
		{
			this->x = other.x;
			this->y = other.y;
			return *this;
		}

		constexpr Rect& operator=(const Vector3Int& other)
		{
			this->x = other.x;
			this->y = other.y;
			return *this;
		}

	private:
		void RenderFunc() override;
		void SetPos(const Vector2& delta) override;
	};


	std::ostream& operator<<(std::ostream& stream, const Rect& other);
}
