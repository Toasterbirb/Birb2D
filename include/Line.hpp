#pragma once

#include "Color.hpp"
#include "SceneObject.hpp"
#include "Vector/Vector2.hpp"

namespace Birb
{
	/* Forward declare the rect struct to avoid
	 * circular include dependency */
	class Rect;

	/* 2 Dimensions lines with point A and B */
	class Line : public SceneObject
	{
	public:
		Line();
		Line(const Vector2& pointA, const Vector2& pointB);
		Line(const Vector2& pointA, const Vector2& pointB, const Color& color);
		Line(const Vector2& pointA, const Vector2& pointB, const Color& color, const int& renderingPriority);

		Vector2 pointA;
		Vector2 pointB;
		Color color; ///< In case the line will be rendered
		int thickness;

		double length() const;
		Rect boundingBox() const;

		bool operator==(const Line& other) const
		{
			return (pointA == other.pointA && pointB == other.pointB);
		}

		bool operator!=(const Line& other) const
		{
			return (pointA != other.pointA || pointB != other.pointB);
		}

	private:
		void RenderFunc() override;
		void SetPos(const Vector2& delta) override;
		void DefaultLineValues();
	};

	inline std::ostream& operator<<(std::ostream& stream, const Line& other)
	{
		stream << "[(" << other.pointA.x << ", " << other.pointA.y << "), (" << other.pointB.x << ", " << other.pointB.y << ")]";
		return stream;
	}
}
