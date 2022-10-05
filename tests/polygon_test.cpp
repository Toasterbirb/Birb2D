#include "doctest.h"
#include "Math.hpp"
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
		Vector2 points[POINT_COUNT] = {
			Vector2(3, 5),
			Vector2(3, 5),
			Vector2(3, 5),
			Vector2(3, 5)
		};

		Polygon polygon(points, POINT_COUNT, 0xAAAAAA);
		CHECK(polygon.size() == POINT_COUNT);
		CHECK(polygon.color == 0xAAAAAA);

		for (int i = 0; i < POINT_COUNT; i++)
			CHECK(polygon.points[i] == points[i]);
	}

	TEST_CASE("Polygon initialization with a vector")
	{
		const int POINT_COUNT = 4;
		std::vector<Vector2> points = {
			Vector2(3, 5),
			Vector2(3, 5),
			Vector2(3, 5),
			Vector2(3, 5)
		};

		Polygon polygon(points, 0xAAAAAA);
		CHECK(polygon.size() == POINT_COUNT);
		CHECK(polygon.color == 0xAAAAAA);

		for (int i = 0; i < POINT_COUNT; i++)
			CHECK(polygon.points[i] == points[i]);

		SUBCASE("Append points to existing polygon")
		{
			std::vector<Vector2> morePointsA = {
				Vector2(3, 5),
				Vector2(3, 5),
				Vector2(3, 5),
				Vector2(3, 5)
			};

			Vector2 morePointsB[POINT_COUNT] = {
				Vector2(3, 5),
				Vector2(3, 5),
				Vector2(3, 5),
				Vector2(4, 5)
			};

			polygon.AddPoints(morePointsA);
			polygon.AddPoints(morePointsB, POINT_COUNT);

			CHECK(polygon.size() == POINT_COUNT * 3);
			CHECK(polygon.points[POINT_COUNT * 3 - 1] == Vector2(4, 5));
		}
	}

	TEST_CASE("Polygon optimization with a lot of points to optimize")
	{
		std::vector<Vector2> points;
		std::vector<Vector2> expectedPoints;

		SUBCASE("Case A")
		{
			points = {
				{2, 0}, /* X */
				{4, 0},
				{5, 1}, /* X? */
				{7, 3},
				{5, 3}, /* X */
				{3, 3}, /* X */
				{1, 3}, /* X */
				{0, 3},
				{0, 2}, /* X */
				{0, 1}, /* X */
				{0, 0}
			};

			expectedPoints = {
				{4, 0},
				//{5, 1},
				{7, 3},
				{0, 3},
				{0, 0}
			};
		}

		SUBCASE("Case B")
		{
			points = {
				{0, 1},
				{0, 0},
				{2, 0},
				{4, 0},
				{4, 2},
				{0, 2}
			};

			expectedPoints = {
				{0, 0},
				{4, 0},
				{4, 2},
				{0, 2}
			};
		}

		SUBCASE("Case C")
		{
			points = {
				{1, 1},
				{2, 0},
				{3, 1},
				{4, 2},
				{3, 3},
				{2, 4},
				{1, 3},
				{0, 2}
			};

			expectedPoints = {
				{2, 0},
				{4, 2},
				{2, 4},
				{0, 2}
			};
		}

		Polygon polygon(points);
		polygon.Optimize();

		CHECK(polygon.points.size() == expectedPoints.size());
		for (size_t i = 0; i < expectedPoints.size(); i++)
			CHECK(polygon.points[i] == expectedPoints[i]);
	}

	TEST_CASE("Find Polygon center point")
	{
		Polygon polygonA({{2, 2}, {8, 3}, {2, 4}});
		CHECK(polygonA.CenterPoint() == Vector2(4, 3));

		Polygon polygonB({
				{1, 2}, {2, 5},
				{4, 3}, {7, 3},
				{5, 1}, {1, 1}});
		CHECK(Birb::Math::Round(polygonB.CenterPoint().x, 2) == 3.33);
		CHECK(polygonB.CenterPoint().y == 2.5f);
	}

	TEST_CASE("Polygon optimization when there are no points to optimize")
	{
		std::vector<Vector2> points;

		SUBCASE("Case A")
		{
			points = {
				{2, 2},
				{4, 1},
				{6, 2},
				{6, 3},
				{-2, 3}
			};
		}

		SUBCASE("Case B")
		{
			points = {
				{-1, -1},
				{ 1, -1},
				{ 1,  1},
				{-1,  1}
			};
		}

		SUBCASE("Case C")
		{
			points = {
				{0, 0},
				{1, 1},
				{2, 0},
				{2, -0.5},
				{4, 0},
				{4, -1},
				{6, 0},
				{5, 0.5},
				{3, 2},
				{1, 3}
			};
		}

		SUBCASE("Case D")
		{
			points = {
				{1, 0},
				{2, 1},
				{0, 1}
			};
		}

		SUBCASE("Polygon where everything would be optimized normally")
		{
			points = {
				{0, 0},
				{1, 0},
				{2, 0},
				{4, 0}
			};
		}

		SUBCASE("Invalid polygon A")
		{
			points = {
				{0, 1},
				{0, 2}
			};
		}

		SUBCASE("Invalid polygon B")
		{
			points = {
				{0, 0}
			};
		}

		Polygon polygon(points);
		polygon.Optimize();

		CHECK(polygon.size() == points.size());
		for (size_t i = 0; i < points.size(); i++)
			CHECK(polygon.points[i] == points[i]);
	}
}
