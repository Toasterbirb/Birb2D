#include "Physics.hpp"
#include "doctest.h"

using namespace Birb;
using namespace Birb::Physics;

namespace BirbTest
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

	TEST_CASE("Detailed Rect collision")
	{
		Rect rectA(1, 1, 3, 1);
		Rect rectB(3, 0, 2, 3);
		Rect rectC(4, 1, 3, 1);
		Rect rectD(2, -1, 4, 2);
		Rect rectE(2, 2, 4, 2);
		Rect rectF(1, 4, 1, 1);
		Rect rectG(5, 2, 1, 1);

		CHECK(RectCollisionDetailed(rectA, rectB) == RectSide::Left);
		CHECK(RectCollisionDetailed(rectB, rectA) == RectSide::Right);

		CHECK(RectCollisionDetailed(rectC, rectB) == RectSide::Right);
		CHECK(RectCollisionDetailed(rectB, rectC) == RectSide::Left);

		CHECK(RectCollisionDetailed(rectD, rectB) == RectSide::Top);
		CHECK(RectCollisionDetailed(rectB, rectD) == RectSide::Bottom);

		CHECK(RectCollisionDetailed(rectE, rectB) == RectSide::Bottom);
		CHECK(RectCollisionDetailed(rectB, rectE) == RectSide::Top);

		CHECK(RectCollisionDetailed(rectF, rectB) == RectSide::None);
		CHECK(RectCollisionDetailed(rectB, rectF) == RectSide::None);

		CHECK(RectCollisionDetailed(rectG, rectB) == RectSide::Right);
		CHECK(RectCollisionDetailed(rectB, rectG) == RectSide::Left);
	}

	TEST_CASE("Floating point in Rect")
	{
		Rect rect(1, 1, 4, 2);

		Vector2 pointA(2, 2);
		CHECK(Physics::PointInRect(rect, pointA));

		Vector2 pointB(4.5, 3.9);
		Vector2 pointC(6.1, 2);
		Vector2 pointD(0.1, -0.2);
		Vector2 pointE(2, 0);

		CHECK_FALSE(Physics::PointInRect(rect, pointB));
		CHECK_FALSE(Physics::PointInRect(rect, pointC));
		CHECK_FALSE(Physics::PointInRect(rect, pointD));
		CHECK_FALSE(Physics::PointInRect(rect, pointE));
	}

	TEST_CASE("Integer point in Rect")
	{
		Rect rect(1, 1, 4, 2);

		Vector2Int pointA(2, 2);
		CHECK(Physics::PointInRect(rect, pointA));

		Vector2Int pointB(4, 4);
		Vector2Int pointC(6, 2);
		Vector2Int pointD(0, 2);
		Vector2Int pointE(2, 0);

		CHECK_FALSE(Physics::PointInRect(rect, pointB));
		CHECK_FALSE(Physics::PointInRect(rect, pointC));
		CHECK_FALSE(Physics::PointInRect(rect, pointD));
		CHECK_FALSE(Physics::PointInRect(rect, pointE));
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
		entityA.localScale = Vector2(2, 1);

		Rect rectB(5, 1, 3, 2);
		entityB.rect = rectB;

		CHECK(EntityCollision(entityA, entityB));
	}

	TEST_CASE("Line intersection")
	{
		Line lineA(Vector2(1, 1), Vector2(5, 3));
		Line lineB(Vector2(4.5f, 1.5f), Vector2(6, 4));
		Line lineC(Vector2(3, 1), Vector2(2, 3));
		Line lineD(Vector2(0,0), Vector2(7, 5));
		Line lineE(Vector2(0, 5), Vector2(7, 0));

		Line lineF(Vector2(7, 1), Vector2(7, 3)); /* This should only collide with its overlapping line */
		//Line lineG(Vector2(7, 2), Vector2(7, 3)); /* This line overlaps with lineF and should collide with it */

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
		Vector2 points[pointCount] = {
			Vector2(0, 0),
			Vector2(2, 0),
			Vector2(3, 2),
			Vector2(4, 0),
			Vector2(4, 3),
			Vector2(0, 3)
		};

		Vector2 testPointA(3, 1); /* Shouldn't be in the polygon */
		Vector2 testPointB(2, 1); /* Should be in the polygon */
		Vector2 testPointC(1, 2); /* Should be in the polygon */
		Vector2 testPointD(3, 4); /* Shouldn't be in the polygon */
		Vector2 testPointE(3.5, 0); /* Shouldn't be in the polygon */
		Vector2 testPointF(-1, 1.5); /* Shouldn't be in the polygon */
		Vector2 testPointG(0, 0); /* Should be in the polygon */

		CHECK_FALSE(PointInPolygon(points, pointCount, testPointA));
		CHECK(PointInPolygon(points, pointCount, testPointB));
		CHECK(PointInPolygon(points, pointCount, testPointC));
		CHECK_FALSE(PointInPolygon(points, pointCount, testPointD));
		CHECK_FALSE(PointInPolygon(points, pointCount, testPointE));
		CHECK_FALSE(PointInPolygon(points, pointCount, testPointF));
		CHECK_FALSE(PointInPolygon(points, pointCount, testPointG));
	}

	TEST_CASE("Polygon collision")
	{
		const int polygonAsize = 7;
		Vector2 polygonA[polygonAsize] = {
			Vector2(2, 1),
			Vector2(4, -1),
			Vector2(9, 1),
			Vector2(7, 3),
			Vector2(10, 4),
			Vector2(5, 5),
			Vector2(1, 4)
		};
		Polygon polyA(polygonA, polygonAsize);

		/* Triangle inside of the polygon A */
		const int polygonBsize = 3;
		Vector2 polygonB[polygonBsize] = {
			Vector2(3, 1),
			Vector2(4, 3),
			Vector2(3, 3)
		};
		Polygon polyB(polygonB, polygonBsize);

		/* 4 sided polygon with no points inside of polygon A, but the sides should collide */
		const int polygonCsize = 4;
		Vector2 polygonC[polygonCsize] = {
			Vector2(8, 3),
			Vector2(9, 3),
			Vector2(9, 6),
			Vector2(7, 6)
		};
		Polygon polyC(polygonC, polygonCsize);

		/* 4 sided polygon completely outside of polygon A, shouldn't collide with it */
		const int polygonDsize = 4;
		Vector2 polygonD[polygonDsize] = {
			Vector2(7, -1),
			Vector2(9, -1),
			Vector2(11, 0),
			Vector2(9, 0)
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

		CHECK(PointInCircle(Vector2Int(3, 2), circle));
		CHECK_FALSE(PointInCircle(Vector2Int(-1, 2), circle));
		CHECK_FALSE(PointInCircle(Vector2Int(4, 4), circle));

		CHECK(PointInCircle(Vector2(3.5f, 2), circle));
		CHECK(PointInCircle(Vector2(3.303f, 0.7386), circle));
		CHECK_FALSE(PointInCircle(Vector2(0.0f, 0.0f), circle));
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

	TEST_CASE("Circle collision with polygons")
	{
		Circle circle(3, {4, 3});

		Polygon polygonA({{1, 6}, {5, 5}, {8, 6}, {5, 7}}, 4);
		Polygon polygonB({{1, 1}, {10, 7}, {10, 8}}, 3);
		Polygon polygonC({{6, 0}, {9, 0}, {9, 5}, {7, 5}, {8, 3}, {7, 1}}, 6);
		Polygon polygonD({{3, 8}, {8, 8}, {8, 10}, {2, 10}}, 4);
		Polygon polygonE({{2, 2}, {3, 2}, {3, 3}, {4, 4}, {2, 4}}, 5);
		Polygon polygonF({{10, 3}, {10, 6}, {2, 7}}, 3);

		CHECK(CircleCollision(circle, polygonA));
		CHECK(CircleCollision(circle, polygonB));
		CHECK_FALSE(CircleCollision(circle, polygonC));
		CHECK_FALSE(CircleCollision(circle, polygonD));
		CHECK(CircleCollision(circle, polygonE));
		CHECK(CircleCollision(circle, polygonF));
	}
}
