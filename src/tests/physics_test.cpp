#include "Physics.hpp"
#include "doctest.h"


namespace Birb
{
	namespace Physics
	{
		TEST_CASE("Rect collision")
		{
			Rect rectA(0, 0, 4, 2);
			Rect rectB(2, 1, 3, 2);
			Rect rectC(5, 1, 3, 2);

			CHECK(RectCollision(rectA, rectB));
			CHECK_FALSE(RectCollision(rectA, rectC));
		}

		TEST_CASE("Rect collision with multiple rects at once in an array")
		{
			Rect rectsA[3] = {
				Rect(0, 0, 4, 2),
				Rect(2, 1, 3, 2),
				Rect(5, 1, 3, 2),
			};

			Rect rectsB[3] = {
				Rect(0, 0, 4, 2),
				Rect(200, 1, 3, 2),
				Rect(5, 100, 3, 2),
			};

			CHECK(RectCollision(rectsA, 3));
			CHECK_FALSE(RectCollision(rectsB, 3));
		}

		TEST_CASE("Rect collision with multiple rects at once in a list")
		{
			std::vector<Rect> rectsA = {
				Rect(0, 0, 4, 2),
				Rect(2, 1, 3, 2),
				Rect(5, 1, 3, 2),
			};

			std::vector<Rect> rectsB = {
				Rect(0, 0, 4, 2),
				Rect(200, 1, 3, 2),
				Rect(5, 100, 3, 2),
			};

			CHECK(RectCollision(rectsA));
			CHECK_FALSE(RectCollision(rectsB));
		}

		TEST_CASE("Entity collision")
		{
			Entity entityA("Entity A");
			Entity entityB("Entity B");
			Entity entityC("Entity C");

			Rect rectA(0, 0, 4, 2);
			entityA.rect = rectA;

			Rect rectB(2, 1, 3, 2);
			entityB.rect = rectB;

			Rect rectC(5, 1, 3, 2);
			entityC.rect = rectC;

			CHECK(EntityCollision(entityA, entityB));
			CHECK_FALSE(EntityCollision(entityA, entityC));
		}

		TEST_CASE("Entity collision with localScale")
		{
			Entity entityA("Entity A");
			Entity entityB("Entity B");

			Rect rectA(0, 0, 4, 2);
			entityA.rect = rectA;
			entityA.localScale = Vector2f(2, 1);

			Rect rectB(5, 1, 3, 2);
			entityB.rect = rectB;

			CHECK(EntityCollision(entityA, entityB));
		}

		TEST_CASE("Line intersection")
		{
			Line lineA(Vector2f(1, 1), Vector2f(5, 3));
			Line lineB(Vector2f(4.5f, 1.5f), Vector2f(6, 4));
			Line lineC(Vector2f(3, 1), Vector2f(2, 3));
			Line lineD(Vector2f(0,0), Vector2f(7, 5));
			Line lineE(Vector2f(0, 5), Vector2f(7, 0));

			Line lineF(Vector2f(7, 1), Vector2f(7, 3)); /* This should only collide with its overlapping line */
			//Line lineG(Vector2f(7, 2), Vector2f(7, 3)); /* This line overlaps with lineF and should collide with it */

			CHECK_FALSE(LineIntersection(lineA, lineB));
			CHECK(LineIntersection(lineA, lineC));
			CHECK(LineIntersection(lineA, lineD));
			CHECK(LineIntersection(lineC, lineD));
			CHECK_FALSE(LineIntersection(lineB, lineD));
			CHECK(LineIntersection(lineA, lineE));
			CHECK(LineIntersection(lineD, lineE));
			CHECK(LineIntersection(lineB, lineE));
			CHECK_FALSE(LineIntersection(lineC, lineE));

			CHECK_FALSE(LineIntersection(lineA, lineF));
			CHECK_FALSE(LineIntersection(lineB, lineF));
			CHECK_FALSE(LineIntersection(lineC, lineF));
			CHECK_FALSE(LineIntersection(lineD, lineF));
			CHECK_FALSE(LineIntersection(lineE, lineF));

			CHECK(LineIntersection(lineF, lineF)); /* Line should collide with itself */
			//CHECK(LineIntersection(lineF, lineG)); /* Not implemented yet */
		}

		TEST_CASE("Point in polygon")
		{
			const int pointCount = 6;
			Vector2f points[pointCount] = {
				Vector2f(0, 0),
				Vector2f(2, 0),
				Vector2f(3, 2),
				Vector2f(4, 0),
				Vector2f(4, 3),
				Vector2f(0, 3)
			};

			Vector2f testPointA(3, 1); /* Shouldn't be in the polygon */
			Vector2f testPointB(2, 1); /* Should be in the polygon */
			Vector2f testPointC(1, 2); /* Should be in the polygon */
			Vector2f testPointD(3, 4); /* Shouldn't be in the polygon */
			Vector2f testPointE(3.5, 0); /* Shouldn't be in the polygon */
			Vector2f testPointF(-1, 1.5); /* Shouldn't be in the polygon */
			Vector2f testPointG(0, 0); /* Should be in the polygon */

			CHECK_FALSE(PointInPolygon(points, pointCount, testPointA));
			CHECK(PointInPolygon(points, pointCount, testPointB));
			CHECK(PointInPolygon(points, pointCount, testPointC));
			CHECK_FALSE(PointInPolygon(points, pointCount, testPointD));
			CHECK_FALSE(PointInPolygon(points, pointCount, testPointE));
			CHECK_FALSE(PointInPolygon(points, pointCount, testPointF));
			CHECK_FALSE(PointInPolygon(points, pointCount, testPointG));
		}

		TEST_CASE("Polygon collisiosn")
		{
			const int polygonAsize = 7;
			Vector2f polygonA[polygonAsize] = {
				Vector2f(2, 1),
				Vector2f(4, -1),
				Vector2f(9, 1),
				Vector2f(7, 3),
				Vector2f(10, 4),
				Vector2f(5, 5),
				Vector2f(1, 4)
			};

			/* Triangle inside of the polygon A */
			const int polygonBsize = 3;
			Vector2f polygonB[polygonBsize] = {
				Vector2f(3, 1),
				Vector2f(4, 3),
				Vector2f(3, 3)
			};

			/* 4 sided polygon with no points inside of polygon A, but the sides should collide */
			const int polygonCsize = 4;
			Vector2f polygonC[polygonCsize] = {
				Vector2f(8, 3),
				Vector2f(9, 3),
				Vector2f(9, 6),
				Vector2f(7, 6)
			};

			/* 4 sided polygon completely outside of polygon A, shouldn't collide with it */
			const int polygonDsize = 4;
			Vector2f polygonD[polygonDsize] = {
				Vector2f(7, -1),
				Vector2f(9, -1),
				Vector2f(11, 0),
				Vector2f(9, 0)
			};

			CHECK(PolygonCollision(polygonA, polygonAsize, polygonB, polygonBsize));
			CHECK(PolygonCollision(polygonA, polygonAsize, polygonC, polygonCsize));
			CHECK_FALSE(PolygonCollision(polygonA, polygonAsize, polygonD, polygonDsize));
		}
	}
}
