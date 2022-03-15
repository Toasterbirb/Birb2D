#pragma once

#include <vector>
#include "Color.hpp"
#include "Vector.hpp"
#include "SceneObject.hpp"

namespace Birb
{
	class Polygon : SceneObject
	{
	public:
		Polygon();
		Polygon(const Color& color);
		Polygon(const Vector2f (&points)[], const int& pointCount);
		Polygon(const Vector2f (&points)[], const int& pointCount, const Color& color);
		Polygon(const std::vector<Vector2f>& points);
		Polygon(const std::vector<Vector2f>& points, const Color& color);

		void AddPoints(const Vector2f (&points)[], const int& pointCount);
		void AddPoints(const std::vector<Vector2f>& points);

		int size() const;

		Color color;
		std::vector<Vector2f> points;

	private:
		void RenderFunc() override;
	};
}
