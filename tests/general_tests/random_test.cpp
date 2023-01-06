#include "doctest.h"
#include "Random.hpp"
#include "Math.hpp"
#include "Logger.hpp"

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Random int")
	{
		Random rand;
		int valueCount = 50;
		int values[50];
		for (int i = 0; i < valueCount; i++)
			values[i] = rand.RandomInt(0, 10);

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

		CHECK(rand.RandomInt(0, 0) == 0);
		CHECK(rand.RandomInt(0, -1) >= 0);

		/* Make sure that the random value is between the correct range */
		int lower_limit = 5;
		int upper_limit = 10;
		int test_count = 1000;
		float out_of_limits_value = 0;

		bool out_of_limits = false;
		for (int i = 0; i < test_count; ++i)
		{
			float value = rand.RandomInt(lower_limit, upper_limit);
			if (value < lower_limit || value > upper_limit)
			{
				out_of_limits_value = value;
				out_of_limits = true;
				break;
			}
		}
		CHECK_FALSE(out_of_limits);

		if (out_of_limits)
			Debug::Log("Limits: " + std::to_string(lower_limit) + " - " + std::to_string(upper_limit) + ". Value: " + std::to_string(out_of_limits_value));
	}

	TEST_CASE("Random float")
	{
		Random rand;
		int valueCount = 50;
		int values[50];
		for (int i = 0; i < valueCount; i++)
			values[i] = rand.RandomFloat(0.0f, 10.0f);

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

		CHECK(rand.RandomFloat(0.0f, 0.0f) == 0.0f);
		CHECK(rand.RandomFloat(0.0f, -1.0f) >= 0.0f);

		/* Make sure that the random value is between the correct range */
		float lower_limit = 5.00f;
		float upper_limit = 6.00f;
		int test_count = 1000;
		float out_of_limits_value = 0;

		bool out_of_limits = false;
		for (int i = 0; i < test_count; ++i)
		{
			float value = rand.RandomFloat(lower_limit, upper_limit);
			if (value < lower_limit || value > upper_limit)
			{
				out_of_limits_value = value;
				out_of_limits = true;
				break;
			}
		}
		CHECK_FALSE(out_of_limits);
		if (out_of_limits)
			Debug::Log("Limits: " + std::to_string(lower_limit) + " - " + std::to_string(upper_limit) + ". Value: " + std::to_string(out_of_limits_value));
	}

	TEST_CASE("Shuffle an integer array")
	{
		Random rand;
		int values[5] = {
			0,
			1,
			2,
			3,
			4
		};

		rand.ShuffleArray(values, 5);

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

		Random::ShuffleArray(values, 5);

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

		Random::ShuffleArray(values, 5);

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

		Random::ShuffleArray(values, 5);

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
