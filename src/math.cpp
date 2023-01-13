#include "Circle.hpp"
#include "Color.hpp"
#include "Line.hpp"
#include "Logger.hpp"
#include "Math.hpp"

constexpr double PI = 3.141592654;

namespace Birb
{
	namespace Math
	{
		Vector2Int Lerp(const Vector2Int& a, const Vector2Int& b, const float& t)
		{
			return Vector2Int(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t));
		}

		Vector3Int Lerp(const Vector3Int& a, const Vector3Int& b, const float& t)
		{
			return Vector3Int(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t), Lerp(a.z, b.z, t));
		}

		Color Lerp(const Color& a, const Color& b, const float& t)
		{
			return Color(Lerp(a.r, b.r, t), Lerp(a.g, b.g, t), Lerp(a.b, b.b, t));
		}


		float CenterPoint(const float& a, const float& b)
		{
			return (a + b) / 2;
		}

		Vector2 CenterPoint(const Vector2& a, const Vector2& b)
		{
			return Vector2(CenterPoint(a.x, b.x), CenterPoint(a.y, b.y));
		}

		Vector2 CenterPoint(const Vector2Int& a, const Vector2Int& b)
		{
			return Vector2(CenterPoint(a.x, b.x), CenterPoint(a.y, b.y));
		}

		Vector3 CenterPoint(const Vector3& a, const Vector3& b)
		{
			return Vector3(CenterPoint(a.x, b.x), CenterPoint(a.y, b.y), CenterPoint(a.z, b.z));
		}

		Vector3 CenterPoint(const Vector3Int& a, const Vector3Int& b)
		{
			return Vector3(CenterPoint(a.x, b.x), CenterPoint(a.y, b.y), CenterPoint(a.z, b.z));
		}

		bool PointOnLine(const Line& line, const Vector2& point)
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

		Vector2 FindPointOnCircle(const Circle& circle, const float& angle)
		{
			/* Convert the angle into radians */
			float radians = (PI / 180) * angle;

			float x = circle.pos.x + circle.radius * cos(radians);
			float y = circle.pos.y + circle.radius * sin(radians);

			return Vector2(x, y);
		}

		Vector2Int FindClosestPoint(const Vector2Int& point, Vector2Int points[], const int& pointCount)
		{
			Vector2Int currentClosestPoint = points[0];
			float currentClosestDistance = VectorDistance(point, points[0]);

			for (int i = 1; i < pointCount; ++i)
			{
				float distance = VectorDistance(point, points[i]);

				/* Compare the distance to the current shortest one. Also set a new closest point if the previous one
				 * was in the exact same position */
				if (distance <= currentClosestDistance || currentClosestDistance == 0.0f)
				{
					currentClosestPoint = points[i];
					currentClosestDistance = distance;
				}
			}
			return currentClosestPoint;
		}

		Vector2Int FindClosestPoint(const Vector2Int& point, const std::vector<Vector2Int>& points)
		{
			Vector2Int currentClosestPoint = points[0];
			float currentClosestDistance = VectorDistance(point, points[0]);

			for (size_t i = 1; i < points.size(); ++i)
			{
				float distance = VectorDistance(point, points[i]);

				/* Compare the distance to the current shortest one. Also set a new closest point if the previous one
				 * was in the exact same position */
				if (distance <= currentClosestDistance || currentClosestDistance == 0.0f)
				{
					currentClosestPoint = points[i];
					currentClosestDistance = distance;
				}
			}
			return currentClosestPoint;
		}


		Vector2Int FindClosestPoint(const Vector2Int& point, const std::vector<Vector2Int>& points, const std::vector<Vector2Int>& ignoredPoints)
		{
			/* Find the first non-ignored point */
			Vector2Int firstNotIgnored;
			for (size_t i = 0; i < points.size(); ++i)
			{
				bool ignored = false;
				for (size_t j = 0; j < ignoredPoints.size(); ++j)
				{
					if (points[i] == ignoredPoints[j])
					{
						ignored = true;
						break;
					}
				}

				if (!ignored)
				{
					firstNotIgnored = points[i];
					break;
				}
			}

			Vector2Int currentClosestPoint = firstNotIgnored;
			float currentClosestDistance = VectorDistance(point, points[0]);

			bool ignore;
			for (size_t i = 1; i < points.size(); ++i)
			{
				ignore = false;

				/* Check if the point is in the ignore list */
				for (size_t j = 0; j < ignoredPoints.size(); ++j)
					if (points[i] == ignoredPoints[j])
					{
						ignore = true;
						break;
					}

				if (!ignore)
				{
					float distance = VectorDistance(point, points[i]);

					/* Compare the distance to the current shortest one. Also set a new closest point if the previous one
					 * was in the exact same position */
					if (distance <= currentClosestDistance || currentClosestDistance == 0.0f)
					{
						currentClosestPoint = points[i];
						currentClosestDistance = distance;
					}
				}
			}
			return currentClosestPoint;
		}

		double 	Normalize(const double& value, const double& min, const double& max, const double& normalized_maximum)
		{
			return ((value - min) / (max - min)) * normalized_maximum;
		}
	}
}
