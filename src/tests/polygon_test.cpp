#include "doctest.h"
#include "Polygon.hpp"

namespace Birb
{
	TEST_CASE("Default polygon")
	{
		Polygon polygon;
		CHECK(polygon.size() == 0);
		CHECK(polygon.color == Color(255, 255, 255, 255));
	}

	TEST_CASE("Polygon initialization with an array")
	{
		const int POINT_COUNT = 4;
		Vector2f points[POINT_COUNT] = {
			Vector2f(3, 5),
			Vector2f(3, 5),
			Vector2f(3, 5),
			Vector2f(3, 5)
		};

		/* clang gives error with this line, but it compiles completely fine with gcc */
		Polygon polygon(points, POINT_COUNT, 0xAAAAAA);
		CHECK(polygon.size() == POINT_COUNT);
		CHECK(polygon.color == 0xAAAAAA);

		for (int i = 0; i < POINT_COUNT; i++)
			CHECK(polygon.points[i] == points[i]);
	}

	TEST_CASE("Polygon initialization with a vector")
	{
		const int POINT_COUNT = 4;
		std::vector<Vector2f> points = {
			Vector2f(3, 5),
			Vector2f(3, 5),
			Vector2f(3, 5),
			Vector2f(3, 5)
		};

		Polygon polygon(points, 0xAAAAAA);
		CHECK(polygon.size() == POINT_COUNT);
		CHECK(polygon.color == 0xAAAAAA);

		for (int i = 0; i < POINT_COUNT; i++)
			CHECK(polygon.points[i] == points[i]);

		SUBCASE("Append points to existing polygon")
		{
			std::vector<Vector2f> morePointsA = {
				Vector2f(3, 5),
				Vector2f(3, 5),
				Vector2f(3, 5),
				Vector2f(3, 5)
			};

			Vector2f morePointsB[POINT_COUNT] = {
				Vector2f(3, 5),
				Vector2f(3, 5),
				Vector2f(3, 5),
				Vector2f(4, 5)
			};

			polygon.AddPoints(morePointsA);
			polygon.AddPoints(morePointsB, POINT_COUNT);

			CHECK(polygon.size() == POINT_COUNT * 3);
			CHECK(polygon.points[POINT_COUNT * 3 - 1] == Vector2f(4, 5));
		}
	}
}
