#pragma once
#include <SDL2/SDL.h>
#include "Utils.hpp"
#include "Entity.hpp"

namespace Birb
{
	namespace Physics
	{
		bool RectCollision(const Rect& rectA, const Rect& rectB);
		bool RectCollision(const Birb::Rect rects[], const int& size);
		bool RectCollision(const std::vector<Birb::Rect>& rects);
		bool EntityCollision(const Entity& entityA, const Entity& entityB);
		bool LineIntersection(const Line& lineA, const Line& lineB);
		bool PointInPolygon(Vector2f points[], const int& pointCount, const Vector2f& point); ///< Test if a given point is inside of the polygon created by a point array
		bool PolygonCollision(Vector2f polygonA[], const int& polygonAsize, Vector2f polygonB[], const int& polygonBsize);
	}
}
