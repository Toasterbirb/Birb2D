#pragma once

#include "Color.hpp"
#include "SceneObject.hpp"
#include "Vector/Vector2.hpp"

#ifdef DISTCC
#include <iosfwd>
#endif

namespace Birb
{
	/* Forward declare the rect struct to avoid
	 * circular include dependency */
	class Rect;

	/* 2 Dimensions lines with point A and B */
	class Line : public SceneObject
	{
	public:
		constexpr Line()
		:pointA(Vector2(0, 0)), pointB(Vector2(0, 0)), color(0xFFFFFF), thickness(1) {}

		Line(const Vector2& pointA, const Vector2& pointB)
		:pointA(pointA), pointB(pointB), color(0xFFFFFF), thickness(1) {}

		Line(const Vector2& pointA, const Vector2& pointB, const Color& color)
		:pointA(pointA), pointB(pointB), color(color), thickness(1) {}

		Line(const Vector2& pointA, const Vector2& pointB, const Color& color, int renderingPriority)
		:pointA(pointA), pointB(pointB), color(color), thickness(1)
		{
			this->renderingPriority = renderingPriority;
		}

		Vector2 pointA;
		Vector2 pointB;
		Color color; ///< In case the line will be rendered
		int thickness;

		constexpr double length() const
		{
			return Math::VectorDistance(pointA, pointB);
		}

		Rect boundingBox() const;

		constexpr bool operator==(const Line& other) const
		{
			return (pointA == other.pointA && pointB == other.pointB);
		}

		constexpr bool operator!=(const Line& other) const
		{
			return (pointA != other.pointA || pointB != other.pointB);
		}

	private:
		void RenderFunc() override;
		void SetPos(const Vector2& delta) override;
	};

	std::ostream& operator<<(std::ostream& stream, const Line& other);
}
