#include "Utils.hpp"
#include "doctest.h"

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Sort path with a startpoint")
	{
		std::vector<Vector2Int> points = {
			Vector2Int(0, 0),
			Vector2Int(3, 3),
			Vector2Int(1, 1),
			Vector2Int(8, 9),
			Vector2Int(6, 6),
		};

		points = utils::SortPath(points[0], points);

		CHECK(points.size() == 5);
		CHECK(points[0] == Vector2Int(0, 0));
		CHECK(points[1] == Vector2Int(1, 1));
		CHECK(points[2] == Vector2Int(3, 3));
		CHECK(points[3] == Vector2Int(6, 6));
		CHECK(points[4] == Vector2Int(8, 9));
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
		SUBCASE("4 point polygon")
		{
			const int polygonSize = 4;
			Vector2 polygon[polygonSize] = {
				Vector2(7, -1),
				Vector2(9, -1),
				Vector2(11, 0),
				Vector2(9, 0),
			};

			Line expectedLines[polygonSize] = {
				Line(Vector2(7, -1), Vector2(9, -1)),
				Line(Vector2(9, -1), Vector2(11, 0)),
				Line(Vector2(11, 0), Vector2(9, 0)),
				Line(Vector2(9, 0), Vector2(7, -1)),
			};

			std::vector<Line> lines = utils::PolygonToLines(polygon, polygonSize);
			CHECK(lines[0] == expectedLines[0]);
			CHECK(lines[1] == expectedLines[1]);
			CHECK(lines[2] == expectedLines[2]);
			CHECK(lines[3] == expectedLines[3]);
			CHECK(lines.size() == 4);
		}

		SUBCASE("3 point polygon")
		{
			const int polygonSize = 3;
			Vector2 polygon[polygonSize] = {
				Vector2(1050, 350),
				Vector2(1075, 400),
				Vector2(1025, 400),
			};

			Line expectedLines[polygonSize] = {
				Line(Vector2(1050, 350), Vector2(1075, 400)),
				Line(Vector2(1075, 400), Vector2(1025, 400)),
				Line(Vector2(1025, 400), Vector2(1050, 350)),
			};

			std::vector<Line> lines = utils::PolygonToLines(polygon, polygonSize);
			CHECK(lines[0] == expectedLines[0]);
			CHECK(lines[1] == expectedLines[1]);
			CHECK(lines[2] == expectedLines[2]);
			CHECK(lines.size() == 3);
		}
	}

	TEST_CASE("Converting 2 dimensional array position into 1 dimension")
	{
		CHECK(utils::FlatIndex({3, 2}, {4, 4}) == 11);
		CHECK(utils::FlatIndex({0, 0}, {4, 4}) == 0);
		CHECK(utils::FlatIndex({2, 2}, {5, 4}) == 12);
		CHECK(utils::FlatIndex({1, 1}, {5, 4}) == 6);
		CHECK(utils::FlatIndex({4, 3}, {5, 4}) == 19);
		CHECK(utils::FlatIndex({1, 2}, {3, 4}) == 7);

		CHECK(utils::FlatIndex({4, 4}, {5, 4}) == -1);
		CHECK(utils::FlatIndex({5, 3}, {5, 4}) == -1);
		CHECK(utils::FlatIndex({-1, 4}, {5, 4}) == -1);
		CHECK(utils::FlatIndex({4, -1}, {5, 4}) == -1);
	}
}
