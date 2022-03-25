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
			CHECK(RectCollision(rectB, rectA));
			CHECK_FALSE(RectCollision(rectA, rectC));
			CHECK_FALSE(RectCollision(rectC, rectA));
			

			Rect rectD(0, 0, 10, 10);
			Rect rectE(0, 20, 10, 10);
			Rect rectF(30, 0, 10, 10);
			Rect rectG(10, 0, 10, 10);

			CHECK(RectCollision(rectG, rectD));
			CHECK(RectCollision(rectD, rectG));
			CHECK_FALSE(RectCollision(rectD, rectE));
			CHECK_FALSE(RectCollision(rectE, rectD));
			CHECK_FALSE(RectCollision(rectE, rectF));
			CHECK_FALSE(RectCollision(rectF, rectE));
			CHECK_FALSE(RectCollision(rectD, rectF));
			CHECK_FALSE(RectCollision(rectF, rectD));
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
			Polygon polyA(polygonA, polygonAsize);

			/* Triangle inside of the polygon A */
			const int polygonBsize = 3;
			Vector2f polygonB[polygonBsize] = {
				Vector2f(3, 1),
				Vector2f(4, 3),
				Vector2f(3, 3)
			};
			Polygon polyB(polygonB, polygonBsize);

			/* 4 sided polygon with no points inside of polygon A, but the sides should collide */
			const int polygonCsize = 4;
			Vector2f polygonC[polygonCsize] = {
				Vector2f(8, 3),
				Vector2f(9, 3),
				Vector2f(9, 6),
				Vector2f(7, 6)
			};
			Polygon polyC(polygonC, polygonCsize);

			/* 4 sided polygon completely outside of polygon A, shouldn't collide with it */
			const int polygonDsize = 4;
			Vector2f polygonD[polygonDsize] = {
				Vector2f(7, -1),
				Vector2f(9, -1),
				Vector2f(11, 0),
				Vector2f(9, 0)
			};
			Polygon polyD(polygonD, polygonDsize);

			/* Test with normal point arrays */
			CHECK(PolygonCollision(polygonA, polygonAsize, polygonB, polygonBsize));
			CHECK(PolygonCollision(polygonB, polygonBsize, polygonA, polygonAsize));

			CHECK(PolygonCollision(polygonA, polygonAsize, polygonC, polygonCsize));
			CHECK(PolygonCollision(polygonC, polygonCsize, polygonA, polygonAsize));

			CHECK_FALSE(PolygonCollision(polygonA, polygonAsize, polygonD, polygonDsize));
			CHECK_FALSE(PolygonCollision(polygonD, polygonDsize, polygonA, polygonAsize));

			/* Test with polygon datatype */
			CHECK(PolygonCollision(polyA, polyB));
			CHECK(PolygonCollision(polyB, polyA));

			CHECK(PolygonCollision(polyA, polyC));
			CHECK(PolygonCollision(polyC, polyA));

			CHECK_FALSE(PolygonCollision(polyA, polyD));
			CHECK_FALSE(PolygonCollision(polyD, polyA));

			/* Check multiple polygon collisions at once */
			CHECK(PolygonCollision({polyA, polyB, polyC}));
			CHECK_FALSE(PolygonCollision({polyA, polyD}));
		}

		TEST_CASE("Point in circle")
		{
			Circle circle(2, {2, 2});

			CHECK(PointInCircle(Vector2int(3, 2), circle));
			CHECK_FALSE(PointInCircle(Vector2int(-1, 2), circle));
			CHECK_FALSE(PointInCircle(Vector2int(4, 4), circle));

			CHECK(PointInCircle(Vector2f(3.5f, 2), circle));
			CHECK(PointInCircle(Vector2f(3.303f, 0.7386), circle));
			CHECK_FALSE(PointInCircle(Vector2f(0.0f, 0.0f), circle));
		}

		TEST_CASE("Circle collision")
		{
			Circle circleA(2, {2, 2});
			Circle circleB(2, {5, 4});
			Circle circleC(3, {10, 4});
			Circle circleD(1, {6, 9});

			CHECK(CircleCollision(circleA, circleB));
			CHECK(CircleCollision(circleB, circleA));

			CHECK(CircleCollision(circleB, circleC));
			CHECK(CircleCollision(circleC, circleB));

			CHECK_FALSE(CircleCollision(circleA, circleC));
			CHECK_FALSE(CircleCollision(circleC, circleA));

			CHECK_FALSE(CircleCollision(circleC, circleD));
			CHECK_FALSE(CircleCollision(circleD, circleC));

			CHECK_FALSE(CircleCollision(circleB, circleD));
			CHECK_FALSE(CircleCollision(circleD, circleB));
		}

		TEST_CASE("Circle collisions with rects")
		{
			Circle circle(1, {4, 5});

			Rect rectA(1, 1, 3, 4);
			Rect rectB(4, 0, 10, 11);
			Rect rectC(5, 4, 1, 2);
			Rect rectD(3, 7, 3, 1);
			Rect rectE(2, 5.8, 1, 1.2);
			Rect rectF(4.5, 1, 2.5, 3);
			Rect rectG(2, 3, 1.2, 1.2);
			Rect rectH(3.8, 6, 0.4, 0.2);

			CHECK(CircleCollision(circle, rectA));
			CHECK(CircleCollision(circle, rectB));
			CHECK(CircleCollision(circle, rectC));
			CHECK_FALSE(CircleCollision(circle, rectD));

			CHECK_FALSE(RectCollision(rectE, circle));
			CHECK_FALSE(RectCollision(rectF, circle));
			CHECK_FALSE(RectCollision(rectG, circle));
			CHECK(RectCollision(rectH, circle));
		}

		TEST_CASE("Circle collision with lines")
		{
			Circle circle(2, {3, 2});
			
			Line lineF({1, 3}, {6, 4});
			Line lineG({1, 4}, {4, 4});
			Line lineH({5, 1}, {5, 2});
			Line lineI({3, 1}, {8, 2});
			Line lineJ({2, 2}, {3, 3});
			Line lineK({3, 5}, {6, 2});
			Line lineL({0, 0}, {5, 10});
			Line lineM({0, 3}, {2, 7});
			Line lineN({8, 3}, {15, 1});
			Line lineO({12, 5}, {12, 10});
			Line lineP({3, 7}, {2, 11});
			Line lineQ({6, 3}, {4, 7});
			Line lineR({1.5, 3.5}, {0, 5});

			CHECK(CircleCollision(circle, lineF));
			CHECK(CircleCollision(circle, lineG));
			CHECK(CircleCollision(circle, lineH));
			CHECK(CircleCollision(circle, lineI));
			CHECK(CircleCollision(circle, lineJ));
			CHECK_FALSE(CircleCollision(circle, lineK));
			CHECK(CircleCollision(circle, lineL));
			CHECK_FALSE(CircleCollision(circle, lineM));
			CHECK_FALSE(CircleCollision(circle, lineN));
			CHECK_FALSE(CircleCollision(circle, lineO));
			CHECK_FALSE(CircleCollision(circle, lineP));
			CHECK_FALSE(CircleCollision(circle, lineQ));
			CHECK_FALSE(CircleCollision(circle, lineR));
		}
	}
}
