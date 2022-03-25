#pragma once

#include "Circle.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Polygon.hpp"

namespace Birb
{
	/// Functions for collision checking etc.
	namespace Physics
	{
		bool RectCollision(const Rect& rectA, const Rect& rectB); ///< Collision between two rects
		bool RectCollision(const Birb::Rect rects[], const int& size); ///< Rect collision with other rects
		bool RectCollision(const std::vector<Birb::Rect>& rects); ///< Rect collision with other rects

		/// Check for collision between a circle and a rect
		bool RectCollision(const Rect& rect, const Circle& circle);

		/// Check for collision between two entities
		bool EntityCollision(const Entity& entityA, const Entity& entityB);

		/// Check if two lines intersect with each other
		bool LineIntersection(const Line& lineA, const Line& lineB);

		/// Check if a point is inside of the polygon
		bool PointInPolygon(Vector2f points[], const int& pointCount, const Vector2f& point);

		/// Check if two polygons collide with each other
		bool PolygonCollision(Vector2f polygonA[], const int& polygonAsize, Vector2f polygonB[], const int& polygonBsize);
		
		/// Check if two polygons collide with each other
		bool PolygonCollision(std::vector<Vector2f> polygonA, std::vector<Vector2f> polygonB);
		
		/// Check if two polygons collide with each other
		bool PolygonCollision(const Polygon& polygonA, const Polygon& polygonB);

		/// Check for collision with multiple polygons
		bool PolygonCollision(std::vector<Polygon> polygons);

		/// Check if a point is inside of a circle
		bool PointInCircle(const Vector2int& point, const Circle& circle);
		
		/// Check if a point is inside of a circle
		bool PointInCircle(const Vector2f& point, const Circle& circle);

		/// Check if a circle is colliding with another circle
		bool CircleCollision(const Circle& circleA, const Circle& circleB);

		/// Check for collision between a circle and a rect
		bool CircleCollision(const Circle& circle, const Rect& rect);

		/// Check for collision between a circle and a line
		bool CircleCollision(const Circle& circle, const Line& line);
	}
}
