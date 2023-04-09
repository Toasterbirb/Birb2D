#include "Polygon.hpp"
#include "Renderwindow.hpp"
#include "PointOnLine.hpp"

constexpr double PI = 3.1415926535897932;

namespace Birb
{
	Polygon::Polygon()
	{
		color = Color(0xFFFFFF);
		angle = 0;
	}

	Polygon::Polygon(const Color& color)
	:color(color)
	{
		angle = 0;
	}

	Polygon::Polygon(const Vector2 points[], int pointCount)
	{
		this->points = std::vector<Vector2>(points, points + pointCount);
		angle = 0;
	}

	Polygon::Polygon(const Vector2 points[], int pointCount, const Color& color)
	:color(color)
	{
		this->points = std::vector<Vector2>(points, points + pointCount);
		angle = 0;
	}

	Polygon::Polygon(const std::vector<Vector2>& points)
	{
		this->points = points;
		angle = 0;
	}

	Polygon::Polygon(const std::vector<Vector2>& points, const Color& color)
	:color(color)
	{
		this->points = points;
		angle = 0;
	}

	void Polygon::AddPoints(const Vector2 points[], int pointCount)
	{
		this->points.insert(std::end(this->points), points, points + pointCount);
	}

	void Polygon::AddPoints(const std::vector<Vector2>& points)
	{
		this->points.insert(std::end(this->points), std::begin(points), std::end(points));
	}

	void Polygon::SetRotation(float new_angle)
	{
		SetRotation(new_angle, CenterPoint());
	}

	void Polygon::SetRotation(float new_angle, const Vector2& pivot_point)
	{
		/* Calculate the difference between the new angle and the old angle
		 * since the rotation math is done on the current position of the points
		 * and not the original ones */
		double angle_difference = new_angle - this->angle;

		double radians = angle_difference * PI / 180;
		double sin = std::sin(radians);
		double cos = std::cos(radians);

		std::vector<Vector2> old_points = points;

		/* Move each of the vertex points individually around the pivot point */
		for (size_t i = 0; i < points.size(); ++i)
		{
			points[i].x = cos * (old_points[i].x - pivot_point.x) - sin * (old_points[i].y - pivot_point.y) + pivot_point.x;
			points[i].y = sin * (old_points[i].x - pivot_point.x) + cos * (old_points[i].y - pivot_point.y) + pivot_point.y;
		}

		/* Update the angle */
		this->angle += angle_difference;
	}

	void Polygon::Translate(const Vector2& delta)
	{
		SetPos(delta);
	}

	Vector2 Polygon::CenterPoint() const
	{
		Vector2 result;

		/* Calculate the average of all points */
		for (size_t i = 0; i < points.size(); ++i)
		{
			result.x += points[i].x;
			result.y += points[i].y;
		}
		result.x /= points.size();
		result.y /= points.size();

		return result;
	}

	bool Polygon::PointsHaveSameAxis(Vector2 point, Vector2 sidePointA, Vector2 sidePointB) const
	{
		bool x = (point.x == sidePointA.x && point.x == sidePointB.x);
		bool y = (point.y == sidePointA.y && point.y == sidePointB.y);

		if (x || y)
		{
			/* The points are on the same x or y -axis */
			return true;
		}

		/* Do some more math to check if the point is on the same *diagonal* line */
		Line line(sidePointA, sidePointB);
		return Math::PointOnLine(line, point);
	}

	/* TODO: Also detect diagonal lines. Currently only supports detecting
	 * unnecessary points along X and Y -axis */
	void Polygon::Optimize()
	{
		/* Don't do anything if the polygon has less than 3 points
		 * since there would be nothing to optimize anyway
		 *
		 * Also in this case the polygon would be invalid to begin with */
		if (points.size() < 4)
			return;

		std::vector<Vector2> newPoints;

		/* Find the first valid point */
		int startPoint = -1;

		/* Check the first point before the loop because it has to be compared
		 * to the last object */
		if (!PointsHaveSameAxis(points[0], points[points.size() - 1], points[1]))
		{
			startPoint = 0;
		}
		else
		{
			/* Loop trough rest of the points to find the first valid point */
			for (size_t i = 1; i < points.size() - 1; ++i)
			{
				if (!PointsHaveSameAxis(points[i], points[i - 1], points[i + 1]))
				{
					startPoint = i;
					break;
				}
			}
		}

		/* We didn't find any valid starting points */
		if (startPoint == -1)
			return;

		/* Push back the first point, since its valid */
		newPoints.push_back(points[startPoint]);

		/* Go trough the polygon points and only keep those points that have
		 * points with all different axis next to them. Don't check the first one
		 * thought, because that has already been checked */
		for (size_t i = startPoint + 1; i < points.size() - 1 && points.size() > 2; ++i)
		{
			if (!PointsHaveSameAxis(points[i], points[i - 1], points[i + 1]))
				newPoints.push_back(points[i]);
		}

		/* The minimum size of a polygon is 3 points, so we need to prevent
		 * cases where the entire polygon would be optimized away */
		if (newPoints.size() < 3)
			return;

		/* Check the last point in the array */
		if (!PointsHaveSameAxis(points[points.size() - 1], points[points.size() - 2], points[0]))
			newPoints.push_back(points[points.size() - 1]);

		points = newPoints;
	}

	int Polygon::size() const
	{
		return points.size();
	}

	void Polygon::RenderFunc()
	{
		Render::DrawPolygon(color, points);
	}

	void Polygon::SetPos(const Vector2& delta)
	{
		for (size_t i = 0; i < points.size(); ++i)
		{
			points[i].x += delta.x;
			points[i].y += delta.y;
		}
	}

	float Polygon::CurrentAngle() const
	{
		return angle;
	}
}
