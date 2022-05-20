#pragma once

#include "Circle.hpp"
#include "Color.hpp"
#include "Entity.hpp"
#include "Line.hpp"
#include "Rect.hpp"
#include "Vector.hpp"

namespace Birb
{
	/// Methods for rendering things
	namespace Render
	{
		bool DrawEntity(Entity& entity); ///< Renders an entity

#ifdef LIB_SDL
		void ResetDrawColor(); ///< Resets the drawing color back to black, so that the window background color stays the same
		void SetRenderDrawColor(const Color& color); ///< Sets the drawing color for base SDL2 drawing functions
#endif

		void DrawRect(const Color& color, const Rect& dimensions); ///< Draw filled rect
		void DrawRect(const Color& color, const Rect& dimensions, const int& width); ///< Draw hollow rect

		void DrawLine(const Color& color, const Vector2int& pointA, const Vector2int& pointB); ///< Draw a line between points A and B
		void DrawLine(const Color& color, const Vector2f& pointA, const Vector2f& pointB); ///< Draw a line between points A and B
		void DrawLine(const Line& line); ///< Draw a line between points A and B
		void DrawLine(const Line& line, const int& thickness); ///< Draw a thick line between points A and B

		void DrawLines(const Color& color, Vector2int* points, const int& pointCount); ///< Draw lines between multiple points at once
		void DrawLines(const Color& color, Vector2f* points, const int& pointCount); ///< Draw lines between multiple points at once

		bool DrawCircle(const Circle& circle); ///< Draw a circle around a point
		bool DrawCircle(const Color& color, const Vector2int& pos, const int& radius); ///< Draw a circle around a point

		bool DrawPolygon(const Color& color, Vector2int* points, const int& pointCount); ///< Draw a polygon from multiple points
		bool DrawPolygon(const Color& color, const std::vector<Vector2int>& points); ///< Draw a polygon from multiple points
		bool DrawPolygon(const Color& color, Vector2f* points, const int& pointCount); ///< Draw a polygon from multiple points
		bool DrawPolygon(const Color& color, const std::vector<Vector2f>& points); ///< Draw a polygon from multiple points
		bool DrawPolygon(const Polygon& polygon); ///< Draw a polygon

	};
}
