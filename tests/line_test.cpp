#include "doctest.h"
#include "Line.hpp"
#include "Math.hpp"

namespace Birb
{
	TEST_CASE("Line constructors")
	{
		Line lineA;
		CHECK(lineA.pointA == Vector2(0, 0));
		CHECK(lineA.pointB == Vector2(0, 0));
		CHECK(lineA.color == Color(255, 255, 255, 255));

		Vector2 vecA(1, 2);
		Vector2 vecB(4, 4);
		Color color(1, 2, 3, 4);

		SUBCASE("Line without color")
		{
			Line lineB(vecA, vecB);
			CHECK(lineB.pointA == vecA);
			CHECK(lineB.pointB == vecB);
			CHECK(lineB.color == Color(255, 255, 255, 255));
		}

		SUBCASE("Line with color")
		{
			Line lineB(vecA, vecB, color);
			CHECK(lineB.pointA == vecA);
			CHECK(lineB.pointB == vecB);
			CHECK(lineB.color == color);
		}

		SUBCASE("Line with color + rendering priority")
		{
			Line lineB(vecA, vecB, color, 10);
			CHECK(lineB.pointA == vecA);
			CHECK(lineB.pointB == vecB);
			CHECK(lineB.color == color);
			CHECK(lineB.renderingPriority == 10);
		}
	}

	TEST_CASE("Get line length")
	{
		Line lineA(Vector2(1, 1), Vector2(8, 2));
		CHECK(Math::Round(lineA.length(), 2) == 7.07);

		Line lineB(Vector2(7, 2), Vector2(4, -1));
		CHECK(Math::Round(lineB.length(), 2) == 4.24);

		Line lineC(Vector2(0, 0), Vector2(4, 0));
		CHECK(lineC.length() == 4);
	}

	TEST_CASE("Get line bounding box as a rect")
	{
		Line lineA(Vector2(1, 1), Vector2(8, 2));
		CHECK(lineA.boundingBox() == Rect(1, 1, 7, 1));

		Line lineB(Vector2(7, 2), Vector2(4, -1));
		CHECK(lineB.boundingBox() == Rect(4, -1, 3, 3));

		Line lineC(Vector2(0, 0), Vector2(4, 0));
		CHECK(lineC.boundingBox() == Rect(0, 0, 4, 0));
	}

	TEST_CASE("Line comparisons")
	{
		Line lineA({0, 0}, {5, 0});
		Line lineB({0, 0}, {5, 0});
		Line lineC({0, 0}, {0, 5});
		Line lineD({0, 1}, {5, 0});
		Line lineE({1, 1}, {5, 4});

		CHECK(lineA == lineB);
		CHECK(lineA != lineC);
		CHECK(lineA != lineD);
		CHECK(lineA != lineE);
	}

}
