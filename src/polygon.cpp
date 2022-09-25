#include "Polygon.hpp"
#include "Renderwindow.hpp"

namespace Birb
{
	Polygon::Polygon()
	{
		color = Color(0xFFFFFF);
	}

	Polygon::Polygon(const Color& color)
	:color(color)
	{}

	Polygon::Polygon(const Vector2f points[], const int& pointCount)
	{
		this->points = std::vector<Vector2f>(points, points + pointCount);
	}

	Polygon::Polygon(const Vector2f points[], const int& pointCount, const Color& color)
	:color(color)
	{
		this->points = std::vector<Vector2f>(points, points + pointCount);
	}

	Polygon::Polygon(const std::vector<Vector2f>& points)
	{
		this->points = points;
	}

	Polygon::Polygon(const std::vector<Vector2f>& points, const Color& color)
	:color(color)
	{
		this->points = points;
	}

	void Polygon::AddPoints(const Vector2f points[], const int& pointCount)
	{
		this->points.insert(std::end(this->points), points, points + pointCount);
	}

	void Polygon::AddPoints(const std::vector<Vector2f>& points)
	{
		this->points.insert(std::end(this->points), std::begin(points), std::end(points));
	}

	Vector2f Polygon::CenterPoint() const
	{
		Vector2f result;

		/* Calculate the average of all points */
		for (int i = 0; i < (int)points.size(); i++)
		{
			result.x += points[i].x;
			result.y += points[i].y;
		}
		result.x /= points.size();
		result.y /= points.size();

		return result;
	}

	bool PointsHaveSameAxis(Vector2f point, Vector2f sidePointA, Vector2f sidePointB)
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

		std::vector<Vector2f> newPoints;

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
			for (int i = 1; i < (int)points.size() - 1; i++)
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
		for (int i = startPoint + 1; i < (int)points.size() - 1 && points.size() > 2; i++)
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

	void Polygon::SetPos(const Vector2f& delta)
	{
		for (int i = 0; i < (int)points.size(); i++)
		{
			points[i].x += delta.x;
			points[i].y += delta.y;
		}
	}
}
