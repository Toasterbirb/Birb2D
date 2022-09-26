#include "doctest.h"
#include "Rect.hpp"

namespace Birb
{
	TEST_CASE("Default Rect")
	{
		Rect defaultRect;
		CHECK(defaultRect.x == 0);
		CHECK(defaultRect.y == 0);
		CHECK(defaultRect.w == 0);
		CHECK(defaultRect.h == 0);

	}

	TEST_CASE("Rect with arguments")
	{
		Rect customRect(10.54, 20, 30.234, 40.6668);
		CHECK(customRect.x == 10.54f);
		CHECK(customRect.y == 20);
		CHECK(customRect.w == 30.234f);
		CHECK(customRect.h == 40.6668f);
	}

	TEST_CASE("Rect to string")
	{
		Rect rectA(10, 20, 30, 40);
		Rect rectB(10.5555f, 20.00f, 30.9000f, 40);
		CHECK(rectA.toString() == "10, 20, 30, 40");
		CHECK(rectB.toString() == "10.5555, 20, 30.9, 40");
	}

	TEST_CASE("Rect to polygon")
	{
		Rect rectA(0, 0, 10, 10);
		Polygon polygonA = rectA.toPolygon();

		CHECK(polygonA.points[0] == Vector2f(0, 0));
		CHECK(polygonA.points[1] == Vector2f(10, 0));
		CHECK(polygonA.points[2] == Vector2f(10, 10));
		CHECK(polygonA.points[3] == Vector2f(0, 10));


		Rect rectB(0, 0, -10, -10);
		Polygon polygonB = rectB.toPolygon();

		CHECK(polygonB.points[0] == Vector2f(0, 0));
		CHECK(polygonB.points[1] == Vector2f(-10, 0));
		CHECK(polygonB.points[2] == Vector2f(-10, -10));
		CHECK(polygonB.points[3] == Vector2f(0, -10));


		Rect rectC(2, 2, 1, 3);
		Polygon polygonC = rectC.toPolygon();

		CHECK(polygonC.points[0] == Vector2f(2, 2));
		CHECK(polygonC.points[1] == Vector2f(3, 2));
		CHECK(polygonC.points[2] == Vector2f(3, 5));
		CHECK(polygonC.points[3] == Vector2f(2, 5));


		Rect rectD(6, 5, 2, 1);
		Polygon polygonD = rectD.toPolygon();

		CHECK(polygonD.points[0] == Vector2f(6, 5));
		CHECK(polygonD.points[1] == Vector2f(8, 5));
		CHECK(polygonD.points[2] == Vector2f(8, 6));
		CHECK(polygonD.points[3] == Vector2f(6, 6));
	}

	TEST_CASE("Rect comparison")
	{
		Rect rectA(10, 10, 10, 10);
		Rect rectB(20, 10, 30, 30);
		Rect rectC(-20, 20, 10, 30);
		Rect rectD(20, 20, 40, -10);

		CHECK(rectA == rectA);
		CHECK(rectA != rectB);
		CHECK(rectA != rectD);
		CHECK_FALSE(rectA == rectB);
		CHECK_FALSE(rectA != rectA);
	}

	TEST_CASE("Get rounded values from Rect")
	{
		Rect rectWithFloats(0.5f, 7.4f, 100.8f, 99.4);
		Rect roundedRect = rectWithFloats.getInt();

		CHECK(roundedRect.x == 1);
		CHECK(roundedRect.y == 7);
		CHECK(roundedRect.w == 101);
		CHECK(roundedRect.h == 99);
	}
}
