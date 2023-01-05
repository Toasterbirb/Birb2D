#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <vector>
#endif

#include "Color.hpp"
#include "SceneObject.hpp"
#include "Vector/Vector2.hpp"

namespace Birb
{
	class Polygon : public SceneObject
	{
	public:
		Polygon();
		Polygon(const Color& color);
		Polygon(const Vector2 points[], const int& pointCount);
		Polygon(const Vector2 points[], const int& pointCount, const Color& color);
		Polygon(const std::vector<Vector2>& points);
		Polygon(const std::vector<Vector2>& points, const Color& color);

		void AddPoints(const Vector2 points[], const int& pointCount);
		void AddPoints(const std::vector<Vector2>& points);

		/// Rotates all of the points in the polygon around its center off mass
		void SetRotation(const float& new_angle);

		/// Rotates all of the points in the polygon around a custom pivot point
		void SetRotation(const float& new_angle, const Vector2& pivot_point);

		/// Move the polygon relatively
		void Translate(const Vector2& delta);

		/// Get the current angle incase it has been changed with SetRotation()
		float CurrentAngle() const;

		/// Gets the "center point" of the polygon by taking the average
		/// of all points
		Vector2 CenterPoint() const;

		/// Removes points that don't change the visual appearance of the polygon
		// Shouldn't be called if the point locations are going to be modified since
		// there is going to be detail lost
		void Optimize();

		/// Returns the point count of the polygon
		int size() const;

		/// The color used to render the polygon
		Color color;

		/// Polygon points / vertices
		std::vector<Vector2> points;

	private:
		bool PointsHaveSameAxis(Vector2 point, Vector2 sidePointA, Vector2 sidePointB) const;

		void RenderFunc() override;
		void SetPos(const Vector2& delta) override;
		float angle;
	};
}
