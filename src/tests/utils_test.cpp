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

	TEST_CASE("Shuffle an integer array")
	{
		int values[5] = {
			0,
			1,
			2,
			3,
			4
		};

		utils::ShuffleArray(values, 5);
		bool shuffleResult = values[0] != 0 || values[1] != 1 || values[2] != 2 || values[3] != 3 || values[4] != 4;
		CHECK(shuffleResult);

		/* Confirm that all of the values are still there */
		int sum = 0;
		for (int i = 0; i < 5; i++)
			sum += values[i];

		CHECK(sum == 10);
	}

	TEST_CASE("Shuffle a float array")
	{
		float values[5] = {
			0.5f,
			1.1f,
			2.6f,
			3,
			4.2f
		};

		utils::ShuffleArray(values, 5);
		bool shuffleResult = values[0] != 0.5f || values[1] != 1.1f || values[2] != 2.6f || values[3] != 3 || values[4] != 4.2f;
		CHECK(shuffleResult);

		/* Confirm that all of the values are still there */
		float sum = 0;
		for (int i = 0; i < 5; i++)
			sum += values[i];

		CHECK(Math::Round(sum, 1) == 11.4);
	}

	TEST_CASE("Shuffle a double array")
	{
		double values[5] = {
			0.5,
			1.1,
			2.6,
			3,
			4.2
		};

		utils::ShuffleArray(values, 5);
		bool shuffleResult = values[0] != 0.5 || values[1] != 1.1 || values[2] != 2.6 || values[3] != 3 || values[4] != 4.2;
		CHECK(shuffleResult);

		/* Confirm that all of the values are still there */
		double sum = 0;
		for (int i = 0; i < 5; i++)
			sum += values[i];

		CHECK(Math::Round(sum, 1) == 11.4);
	}
	
	TEST_CASE("Shuffle a string array")
	{
		std::string originalValues[5] = {
			"One",
			"Two",
			"Three",
			"Four",
			"Five"
		};

		std::string values[5] = {
			"One",
			"Two",
			"Three",
			"Four",
			"Five"
		};

		utils::ShuffleArray(values, 5);
		bool shuffleResult = values[0] != "One" || values[1] != "Two" || values[2] != "Three" || values[3] != "Four" || values[4] != "Five";
		CHECK(shuffleResult);

		/* Confirm that all of the values are still there */
		bool valueFound[5];

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				if (i == j)
					valueFound[i] = true;
		
		/* Check the results */
		bool result = true;

		for (int i = 0; i < 5; i++)
			if (valueFound[i] == false)
			{
				result = false;
				break;
			}

		CHECK(result);
	}
}
