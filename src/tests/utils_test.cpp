#include "Utils.hpp"
#include "doctest.h"


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
		Vector2f* polygonA = rectA.toPolygon();

		CHECK(polygonA[0] == Vector2f(0, 0));
		CHECK(polygonA[1] == Vector2f(10, 0));
		CHECK(polygonA[2] == Vector2f(10, 10));
		CHECK(polygonA[3] == Vector2f(0, 10));

		Rect rectB(0, 0, -10, -10);
		Vector2f* polygonB = rectB.toPolygon();

		CHECK(polygonB[0] == Vector2f(0, 0));
		CHECK(polygonB[1] == Vector2f(-10, 0));
		CHECK(polygonB[2] == Vector2f(-10, -10));
		CHECK(polygonB[3] == Vector2f(0, -10));
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


	TEST_CASE("Sort path with a startpoint")
	{
		std::vector<Vector2int> points = {
			Vector2int(0, 0),
			Vector2int(3, 3),
			Vector2int(1, 1),
			Vector2int(8, 9),
			Vector2int(6, 6),
		};

		points = utils::SortPath(points[0], points);

		CHECK(points.size() == 5);
		CHECK(points[0] == Vector2int(0, 0));
		CHECK(points[1] == Vector2int(1, 1));
		CHECK(points[2] == Vector2int(3, 3));
		CHECK(points[3] == Vector2int(6, 6));
		CHECK(points[4] == Vector2int(8, 9));
	}

	TEST_CASE("Create a string out of floating point number without trailing zeroes in decimals")
	{
		double values[7] = {
			1.987200,
			2.0000,
			4.3429000,
			4.00,
			5.020,
			-1.0001,
			-1.555
		};

		CHECK(utils::CleanDecimals(values[0]) == "1.9872");
		CHECK(utils::CleanDecimals(values[1]) == "2");
		CHECK(utils::CleanDecimals(values[2]) == "4.3429");
		CHECK(utils::CleanDecimals(values[3]) == "4");
		CHECK(utils::CleanDecimals(values[4]) == "5.02");
		CHECK(utils::CleanDecimals(values[5]) == "-1.0001");
		CHECK(utils::CleanDecimals(values[6]) == "-1.555");
	}

	TEST_CASE("Polygon to lines")
	{
		const int polygonSize = 4;
		Vector2f polygon[polygonSize] = {
			Vector2f(7, -1),
			Vector2f(9, -1),
			Vector2f(11, 0),
			Vector2f(9, 0),
		};

		Line expectedLines[polygonSize] = {
			Line(Vector2f(7, -1), Vector2f(9, -1)),
			Line(Vector2f(9, -1), Vector2f(11, 0)),
			Line(Vector2f(11, 0), Vector2f(9, 0)),
			Line(Vector2f(9, 0), Vector2f(7, -1)),
		};

		Line* lines = utils::PolygonToLines(polygon, polygonSize);
		CHECK(lines[0] == expectedLines[0]);
		CHECK(lines[1] == expectedLines[1]);
		CHECK(lines[2] == expectedLines[2]);
		CHECK(lines[3] == expectedLines[3]);
	}
}
