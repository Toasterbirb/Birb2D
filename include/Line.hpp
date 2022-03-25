#pragma once

#include "Color.hpp"
#include "SceneObject.hpp"
#include "Vector.hpp"

namespace Birb
{
	/* 2 Dimensions lines with point A and B */
	class Line : public SceneObject
	{
	public:
		Line();
		Line(const Vector2f& pointA, const Vector2f& pointB);
		Line(const Vector2f& pointA, const Vector2f& pointB, const Color& color);
		Line(const Vector2f& pointA, const Vector2f& pointB, const Color& color, const int& renderingPriority);

		Vector2f pointA;
		Vector2f pointB;
		Color color; ///< In case the line will be rendered

		bool operator==(const Line& other) const
		{
			return (pointA == other.pointA && pointB == other.pointB);
		}

		bool operator!=(const Line& other) const
		{
			return (pointA == other.pointA && pointB == other.pointB);
		}

	private:
		void RenderFunc() override;
	};

	inline std::ostream& operator<<(std::ostream& stream, const Line& other)
	{
		stream << "[(" << other.pointA.x << ", " << other.pointA.y << "), (" << other.pointB.x << ", " << other.pointB.y << ")]";
		return stream;
	}
}
