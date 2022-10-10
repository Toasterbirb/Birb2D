#pragma once

#include "SDL.hpp"

#include "Color.hpp"
#include "Line.hpp"
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
		std::vector<Line> toLines() const; ///< Returns the four sides of the rect as lines
		Rect getInt() const;
		Vector2 centerPoint() const;

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

		bool operator!=(const Rect& other) const
		{
			return 	(x != other.x
					|| y != other.y
					|| w != other.w
					|| h != other.h);
		}

		Rect& operator=(const Vector2& other)
		{
			this->x = other.x;
			this->y = other.y;
			return *this;
		}

		Rect& operator=(const Vector2Int& other)
		{
			this->x = other.x;
			this->y = other.y;
			return *this;
		}

		Rect& operator=(const Vector3& other)
		{
			this->x = other.x;
			this->y = other.y;
			return *this;
		}

		Rect& operator=(const Vector3Int& other)
		{
			this->x = other.x;
			this->y = other.y;
			return *this;
		}

	private:
		void RenderFunc() override;
		void SetPos(const Vector2& delta) override;
	};


	inline std::ostream& operator<<(std::ostream& stream, const Rect& other)
	{
		stream << other.x << ", " << other.y << ", " << other.w << ", " << other.h;
		return stream;
	}
}
