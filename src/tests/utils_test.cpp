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

	TEST_CASE("Get rounded values from Rect")
	{
		Rect rectWithFloats(0.5f, 7.4f, 100.8f, 99.4);
		Rect roundedRect = rectWithFloats.getInt();

		CHECK(roundedRect.x == 1);
		CHECK(roundedRect.y == 7);
		CHECK(roundedRect.w == 101);
		CHECK(roundedRect.h == 99);
	}

	TEST_CASE("Random int")
	{
		/* Make sure that the functions return a different value every time */
		utils::InitRandomGen();

		int valueCount = 50;
		int values[50];
		for (int i = 0; i < valueCount; i++)
			values[i] = utils::randomInt(0, 10);

		/* Check if all of the values were the same */
		int firstValue = values[0];
		bool differentValueFound = false;
		for (int i = 1; i < valueCount; i++)
		{
			//std::cout << "[" << i << "] Randon value: " << values[i] << std::endl;
			if (values[i] != firstValue)
			{
				differentValueFound = true;
				//break;
			}
		}

		CHECK(differentValueFound);
	}

	TEST_CASE("Random float")
	{
		/* Make sure that the functions return a different value every time */
		utils::InitRandomGen();

		int valueCount = 50;
		int values[50];
		for (int i = 0; i < valueCount; i++)
			values[i] = utils::randomFloat(0.0f, 10.0f);

		/* Check if all of the values were the same */
		float firstValue = values[0];
		bool differentValueFound = false;
		for (int i = 1; i < valueCount; i++)
		{
			//std::cout << "[" << i << "] Randon value: " << values[i] << std::endl;
			if (values[i] != firstValue)
			{
				differentValueFound = true;
				//break;
			}
		}

		CHECK(differentValueFound);
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

	TEST_CASE("Create a string out of double/float without trailing zeroes in decimals")
	{
		float valueA = 1.987200;
		float valueB = 2.0000;
		double valueC = 4.3429000;
		double valueD = 4.00;

		CHECK(utils::CleanDecimals(valueA) == "1.9872");
		CHECK(utils::CleanDecimals(valueB) == "2");
		CHECK(utils::CleanDecimals(valueC) == "4.3429");
		CHECK(utils::CleanDecimals(valueD) == "4");
	}
}
