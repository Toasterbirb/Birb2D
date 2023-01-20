#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <vector>
#endif

#include "BaseEntity.hpp"

namespace Birb
{
	class Circle;
	class Line;
	class Polygon;
	class Rect;
	class Vector2;
	class Vector2Int;

	/// Functions for collision checking etc.
	namespace Physics
	{
		/// Collision between two rects
		bool RectCollision(const Rect& rectA, const Rect& rectB);

		/// Rect collision with other rects
		bool RectCollision(const Birb::Rect rects[], const int& size);

		/// Rect collision with other rects
		bool RectCollision(const std::vector<Birb::Rect>& rects);

		/// Check for collision between a circle and a rect
		bool RectCollision(const Rect& rect, const Circle& circle);

		enum RectSide
		{
			Left, Right, Top, Bottom, None
		};

		/// Collision between two rects with information
		/// about the collision side
		RectSide RectCollisionDetailed(const Rect& rectA, const Rect& rectB);

		/// Check if a float 2D point is inside of a rect
		bool PointInRect(const Rect& rect, const Vector2& point);

		/// Check if an integer 2D point is inside of a rect
		bool PointInRect(const Rect& rect, const Vector2Int& point);

		/// Check for collision between two entities
		bool EntityCollision(const BaseEntity& entityA, const BaseEntity& entityB);

		/// Check if two lines intersect with each other
		bool LineIntersection(const Line& lineA, const Line& lineB);

		/// Check if a point is inside of the polygon
		bool PointInPolygon(Vector2 points[], const int& pointCount, const Vector2& point);

		/// Check if two polygons collide with each other
		bool PolygonCollision(Vector2 polygonA[], const int& polygonAsize, Vector2 polygonB[], const int& polygonBsize);

		/// Check if two polygons collide with each other
		bool PolygonCollision(std::vector<Vector2> polygonA, std::vector<Vector2> polygonB);

		/// Check if two polygons collide with each other
		bool PolygonCollision(const Polygon& polygonA, const Polygon& polygonB);

		/// Check for collision with multiple polygons
		bool PolygonCollision(std::vector<Polygon> polygons);

		/// Check if a point is inside of a circle
		bool PointInCircle(const Vector2Int& point, const Circle& circle);

		/// Check if a point is inside of a circle
		bool PointInCircle(const Vector2& point, const Circle& circle);

		/// Check if a circle is colliding with another circle
		bool CircleCollision(const Circle& circleA, const Circle& circleB);

		/// Check for collision between a circle and a rect
		bool CircleCollision(const Circle& circle, const Rect& rect);

		/// Check for collision between a circle and a line
		bool CircleCollision(const Circle& circle, const Line& line);

		/// Check for collision between a circle and a polygon
		bool CircleCollision(const Circle& circle, const Polygon& polygon);
	}
}
