#pragma once
#include "Line.hpp"

namespace Birb
{
	namespace Math
	{
		/// Check if the give point is on the line
		constexpr bool PointOnLine(const Line& line, const Vector2& point)
		{
			/* Check if the point is in the area of the line
			 *
			 * A point could be "on the line", but it might be outside of the line limited
			 * by pointA and pointB */
			if (std::min(line.pointA.x, line.pointB.x) > point.x
				|| std::max(line.pointA.x, line.pointB.x) < point.x
				|| std::min(line.pointA.y, line.pointB.y) > point.y
				|| std::max(line.pointA.y, line.pointB.y) < point.y)
			{
				return false;
			}

			float slope = (line.pointB.y - line.pointA.y) / (line.pointB.x - line.pointA.x);
			float y_intersection = line.pointA.y - (line.pointA.x * slope);

			return (point.y == (slope * point.x + y_intersection));
		}

	}
}
