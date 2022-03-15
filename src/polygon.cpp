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

	int Polygon::size() const
	{
		return points.size();
	}

	void Polygon::RenderFunc()
	{
		Render::DrawPolygon(color, points);
	}
}
