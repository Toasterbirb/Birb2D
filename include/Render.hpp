#pragma once
#include "Color.hpp"
#include "BaseEntity.hpp"
#include "Line.hpp"
#include "Rect.hpp"
#include "Vector/Vector2.hpp"
#include "Vector/Vector2Int.hpp"

namespace Birb
{
	class Circle;
	class Texture;

	namespace Render
	{
		void ResetDrawColor(); ///< Resets the drawing color back to black, so that the window background color stays the same
		void SetRenderDrawColor(const Color& color); ///< Sets the drawing color for base SDL2 drawing functions

		bool DrawTexture(const Texture& texture, const Rect& rect, const bool& world_space = true, const float& angle = 0.0f);
		bool DrawTexture(const Texture& texture, const SDL_Rect& src, const SDL_Rect& dst, const float& angle = 0.0f);

		void DrawRect(const Rect& rect); ///< Draw filled rect
		void DrawRect(const Color& color, const Rect& dimensions); ///< Draw filled rect
		void DrawRect(const Color& color, const Rect& dimensions, const int& width); ///< Draw hollow rect

		void DrawLine(const Color& color, const Vector2Int& pointA, const Vector2Int& pointB, const bool& world_space = true, const float& parallax_multiplier = 1); ///< Draw a line between points A and B
		void DrawLine(const Color& color, const Vector2& pointA, const Vector2& pointB, const bool& world_space = true, const float& parallax_multiplier = 1); ///< Draw a line between points A and B
		void DrawLine(const Line& line); ///< Draw a line between points A and B
		void DrawLine(const Line& line, const int& thickness); ///< Draw a thick line between points A and B

		void DrawLines(const Color& color, Vector2Int* points, const int& pointCount, const bool& world_space = true, const float& parallax_multiplier = 1); ///< Draw lines between multiple points at once
		void DrawLines(const Color& color, Vector2* points, const int& pointCount, const bool& world_space = true, const float& parallax_multiplier = 1); ///< Draw lines between multiple points at once

		bool DrawCircle(const Circle& circle); ///< Draw a circle around a point
		bool DrawCircle(const Color& color, const Vector2Int& pos, const int& radius, const bool& world_space = true, const float& parallax_multiplier = 1); ///< Draw a circle around a point

		bool DrawPolygon(const Color& color, Vector2Int* points, const int& pointCount, const bool& world_space = true, const float& parallax_multiplier = 1); ///< Draw a polygon from multiple points
		bool DrawPolygon(const Color& color, const std::vector<Vector2Int>& points, const bool& world_space = true, const float& parallax_multiplier = 1); ///< Draw a polygon from multiple points
		bool DrawPolygon(const Color& color, Vector2* points, const int& pointCount, const bool& world_space = true, const float& parallax_multiplier = 1); ///< Draw a polygon from multiple points
		bool DrawPolygon(const Color& color, const std::vector<Vector2>& points, const bool& world_space = true, const float& parallax_multiplier = 1); ///< Draw a polygon from multiple points
		bool DrawPolygon(const Polygon& polygon); ///< Draw a polygon
	}
}
