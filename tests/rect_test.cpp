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

		CHECK(polygonA.points[0] == Vector2(0, 0));
		CHECK(polygonA.points[1] == Vector2(10, 0));
		CHECK(polygonA.points[2] == Vector2(10, 10));
		CHECK(polygonA.points[3] == Vector2(0, 10));


		Rect rectB(0, 0, -10, -10);
		Polygon polygonB = rectB.toPolygon();

		CHECK(polygonB.points[0] == Vector2(0, 0));
		CHECK(polygonB.points[1] == Vector2(-10, 0));
		CHECK(polygonB.points[2] == Vector2(-10, -10));
		CHECK(polygonB.points[3] == Vector2(0, -10));


		Rect rectC(2, 2, 1, 3);
		Polygon polygonC = rectC.toPolygon();

		CHECK(polygonC.points[0] == Vector2(2, 2));
		CHECK(polygonC.points[1] == Vector2(3, 2));
		CHECK(polygonC.points[2] == Vector2(3, 5));
		CHECK(polygonC.points[3] == Vector2(2, 5));


		Rect rectD(6, 5, 2, 1);
		Polygon polygonD = rectD.toPolygon();

		CHECK(polygonD.points[0] == Vector2(6, 5));
		CHECK(polygonD.points[1] == Vector2(8, 5));
		CHECK(polygonD.points[2] == Vector2(8, 6));
		CHECK(polygonD.points[3] == Vector2(6, 6));
	}

	TEST_CASE("Rect to lines")
	{
		Rect rectA(0, 0, 4, 2);
		std::vector<Line> lines = rectA.toLines();

		CHECK(lines[0] == Line({0, 0}, {4, 0}));
		CHECK(lines[1] == Line({4, 0}, {4, 2}));
		CHECK(lines[2] == Line({4, 2}, {0, 2}));
		CHECK(lines[3] == Line({0, 2}, {0, 0}));

		Rect rectB(-2, -2, 3, 4);
		lines = rectB.toLines();

		CHECK(lines[0] == Line({-2, -2}, {1, -2}));
		CHECK(lines[1] == Line({1, -2}, {1, 2}));
		CHECK(lines[2] == Line({1, 2}, {-2, 2}));
		CHECK(lines[3] == Line({-2, 2}, {-2, -2}));
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

	TEST_CASE("Calculate the centerpoint of a rect")
	{
		CHECK(Rect(0, 0, 7, 4).centerPoint() == Vector2(3.5, 2));
		CHECK(Rect(2, 1, 13, 7).centerPoint() == Vector2(8.5, 4.5));
		CHECK(Rect(1, -2, 5, 7).centerPoint() == Vector2(3.5, 1.5));
	}

	TEST_CASE("Set rect position with a vector")
	{
		Rect rect(1, 2, 3, 4);

		Vector2 vec2(5, 5);
		Vector2Int vec2int(6, 6);
		Vector3 vec3(7, 7, 7);
		Vector3Int vec3int(8, 8, 8);

		rect = vec2;
		CHECK(rect == Rect(5, 5, 3, 4));

		rect = vec2int;
		CHECK(rect == Rect(6, 6, 3, 4));

		rect = vec3;
		CHECK(rect == Rect(7, 7, 3, 4));

		rect = vec3int;
		CHECK(rect == Rect(8, 8, 3, 4));
	}
}
