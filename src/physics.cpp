#include "Physics.hpp"

namespace Birb
{
	namespace Physics
	{
		bool RectCollision(const Rect& rectA, const Rect& rectB)
		{
			SDL_Rect A = rectA.getSDLRect();
			SDL_Rect B = rectB.getSDLRect();

			return SDL_HasIntersection(&A, &B);
		}

		bool RectCollision(const Birb::Rect rects[], const int& size)
		{
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					if (i != j && RectCollision(rects[i], rects[j]))
						return true;
			return false;
		}

		bool RectCollision(const std::vector<Birb::Rect>& rects)
		{
			for (int i = 0; i < (int)rects.size(); i++)
				for (int j = 0; j < (int)rects.size(); j++)
					if (i != j && RectCollision(rects[i], rects[j]))
						return true;
			return false;
		}

		bool EntityCollision(const Entity& entityA, const Entity& entityB)
		{
			SDL_Rect A = entityA.rect.getSDLRect();
			SDL_Rect B = entityB.rect.getSDLRect();

			/* Take localscale into account */
			A.w *= entityA.localScale.x;
			A.h *= entityA.localScale.y;
			B.w *= entityB.localScale.x;
			B.h *= entityB.localScale.y;

			return SDL_HasIntersection(&A, &B);
		}

		/* Inspired/yoinked from
		 * https://stackoverflow/questions/563198/how-do-you-detect-where-two-line-segments-intersect
		 *
		 * Doesn't handle cases where the lines overlap eachother and have the exact same X/Y values
		 * for example A(7,1) B(7,3) and A(7,2) B(7,3) should technically collide, but this algorithm 
		 * doesn't handle it for some reason. pls fix*/
		bool LineIntersection(const Line& lineA, const Line& lineB)
		{
			/* If the two lines are the exact same, they should collide */
			if (lineA == lineB)
				return true;

			float s1_x, s1_y, s2_x, s2_y;

			/* Line A */
			s1_x = lineA.pointB.x - lineA.pointA.x;
			s1_y = lineA.pointB.y - lineA.pointA.y;

			/* Line B */
			s2_x = lineB.pointB.x - lineB.pointA.x;
			s2_y = lineB.pointB.y - lineB.pointA.y;

			float s, t;
			s = (-s1_y * (lineA.pointA.x - lineB.pointA.x) + s1_x * (lineA.pointA.y - lineB.pointA.y)) / (-s2_x * s1_y + s1_x * s2_y);
			t = ( s2_x * (lineA.pointA.y - lineB.pointA.y) - s2_y * (lineA.pointA.x - lineB.pointA.x)) / (-s2_x * s1_y + s1_x * s2_y);

			if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
			{
				/* Intersection found */
				return true;
			}

			return false;
		}

		/* Inspired/yoinked from https://alienryderflex.com/polygon */
		bool PointInPolygon(Vector2f points[], const int& pointCount, const Vector2f& point)
		{
			int j = pointCount - 1;
			bool oddNodes = false; /* If the node count is odd, the point is in the polygon */
			
			for (int i = 0; i < pointCount; i++)
			{
				if (points[i].y < point.y && points[j].y >= point.y
						|| points[j].y < point.y && points[i].y >= point.y)
				{
					if (points[i].x + (point.y - points[i].y) / (points[j].y - points[i].y) * (points[j].x - points[i].x) < point.x)
					{
						oddNodes = !oddNodes;
					}
				}

				j = i;
			}

			return oddNodes;
		}

		bool PolygonCollision(Vector2f polygonA[], const int& polygonAsize, Vector2f polygonB[], const int& polygonBsize)
		{
			/* First test if any of the points of either polygon is inside of the other one
			 * start with polygon A and then repeat the process the other way around */
			for (int i = 0; i < polygonAsize; i++)
				if (PointInPolygon(polygonB, polygonBsize, polygonA[i]))
					return true;

			for (int i = 0; i < polygonBsize; i++)
				if (PointInPolygon(polygonA, polygonAsize, polygonB[i]))
					return true;

			/* Next check for line intersections. The other polygon might not have points inside of the other polygon
			 * so we need to check if the sides intersect. First convert the polygons into lines */
			Line* polygonAlines = utils::PolygonToLines(polygonA, polygonAsize);
			Line* polygonBlines = utils::PolygonToLines(polygonB, polygonBsize);

			/* Check if any of the lines intersect */
			for (int i = 0; i < polygonAsize; i++)
			{
				for (int j = 0; j < polygonBsize; j++)
				{
					if (LineIntersection(polygonAlines[i], polygonBlines[j]))
						return true;
				}
			}

			return false;
		}
	}
}
