#include "doctest.h"
#include "Line.hpp"

namespace Birb
{
	TEST_CASE("Line constructors")
	{
		Line lineA;
		CHECK(lineA.pointA == Vector2f(0, 0));
		CHECK(lineA.pointB == Vector2f(0, 0));
		CHECK(lineA.color == Color(255, 255, 255, 255));

		Vector2f vecA(1, 2);
		Vector2f vecB(4, 4);
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
}
