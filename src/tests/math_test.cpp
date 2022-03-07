#include "Math.hpp"
#include "doctest.h"

namespace Birb
{
	TEST_CASE("Distance calculation with 2D vectors")
	{
		Vector2f pointAf(1.0f, 1.0f);
		Vector2f pointBf(8.0f, 3.0f);

		Vector2int pointAint(1, 1);
		Vector2int pointBint(8, 3);

		CHECK(Math::VectorDistance(pointAf, pointBf) == 7.2801098892805f);
		CHECK(Math::VectorDistance(pointAint, pointBint) == 7.2801098892805f);
	}

	TEST_CASE("Distance calculation with 3D vectors")
	{
		Vector3f pointAf(1.0f, 1.0f, 1.0f);
		Vector3f pointBf(8.0f, 3.0f, 2.0f);

		Vector3int pointAint(1, 1, 1);
		Vector3int pointBint(8, 3, 2);

		CHECK(std::roundf(Math::VectorDistance(pointAf, pointBf)) == std::roundf(7.3484792283495));
		CHECK(std::roundf(Math::VectorDistance(pointAint, pointBint)) == std::roundf(7.3484692283495));
	}

	TEST_CASE("float clamping")
	{
		float floatvalue = 15;

		CHECK(Math::Clamp(floatvalue, 0.0f, 5.0f) == 5.0f);
		CHECK(Math::Clamp(floatvalue, 0.0f, 20.0f) == 15.0f);
		CHECK(Math::Clamp(floatvalue, 20.0f, 40.0f) == 20.0f);
		CHECK(Math::Clamp(floatvalue, 40.0f, 5.0f) == 40.0f);
	}

	TEST_CASE("double clamping")
	{
		double doublevalue = 20;

		CHECK(Math::Clamp(doublevalue, 0.0, 5.0) == 5.0);
		CHECK(Math::Clamp(doublevalue, 0.0, 25.0) == 20.0);
		CHECK(Math::Clamp(doublevalue, 25.0, 40.0) == 25.0);
		CHECK(Math::Clamp(doublevalue, 40.0, 5.0) == 40);
	}

	TEST_CASE("integer clamping")
	{
		int intvalue = 10;

		CHECK(Math::Clamp(intvalue, 0, 5) == 5);
		CHECK(Math::Clamp(intvalue, 0, 20) == 10);
		CHECK(Math::Clamp(intvalue, 20, 40) == 20);
		CHECK(Math::Clamp(intvalue, 40, 5) == 40);
	}

	TEST_CASE("Lerping / interpolation with integers")
	{
		int a = 1;
		int b = 10;

		CHECK(Math::Lerp(a, b, 0) == 1);
		CHECK(Math::Lerp(a, b, 0.5) == 6);
		CHECK(Math::Lerp(a, b, 0.75) == 8);
		CHECK(Math::Lerp(a, b, 1) == 10);
	}

	TEST_CASE("Lerping / interpolation with floats")
	{
		float a = 1;
		float b = 3;

		CHECK(Math::Lerp(a, b, 0) == 1);
		CHECK(Math::Lerp(a, b, 0.25) == 1.5f);
		CHECK(Math::Lerp(a, b, 0.5) == 2);
		CHECK(Math::Lerp(a, b, 1) == 3);
	}

	TEST_CASE("Lerping / interpolation with 2D float vectors")
	{
		Vector2f vecAf = { 1.0f, 1.0f };
		Vector2f vecBf = { 4.0f, 2.0f };

		CHECK(Math::Lerp(vecAf, vecBf, 0) == Birb::Vector2f(1, 1));
		CHECK(Math::Lerp(vecAf, vecBf, 0.5) == Birb::Vector2f(2.5, 1.5));
		CHECK(Math::Lerp(vecAf, vecBf, 0.75) == Birb::Vector2f(3.25, 1.75));
		CHECK(Math::Lerp(vecAf, vecBf, 1) == Birb::Vector2f(4, 2));
	}

	TEST_CASE("Lerping / interpolation with 2D integer vectors")
	{
		Vector2int vecAint = { 10, 10 };
		Vector2int vecBint = { 40, 20 };

		CHECK(Math::Lerp(vecAint, vecBint, 0) == Birb::Vector2int(10, 10));
		CHECK(Math::Lerp(vecAint, vecBint, 0.5) == Birb::Vector2int(25, 15));
		CHECK(Math::Lerp(vecAint, vecBint, 0.75) == Birb::Vector2int(33, 18));
		CHECK(Math::Lerp(vecAint, vecBint, 1) == Birb::Vector2int(40, 20));
	}

	TEST_CASE("Lerping / interpolation with 3D float vectors")
	{
		Vector3f vecAf = { 1.0f, 1.0f, 1.0f };
		Vector3f vecBf = { 4.0f, 2.0f, 3.0f };

		CHECK(Math::Lerp(vecAf, vecBf, 0) == Birb::Vector3f(1, 1, 1));
		CHECK(Math::Lerp(vecAf, vecBf, 0.5) == Birb::Vector3f(2.5, 1.5, 2));
		CHECK(Math::Lerp(vecAf, vecBf, 0.75) == Birb::Vector3f(3.25, 1.75, 2.5));
		CHECK(Math::Lerp(vecAf, vecBf, 1) == Birb::Vector3f(4, 2, 3));
	}

	TEST_CASE("Lerping / interpolation with 3D integer vectors")
	{
		Vector3int vecAint = { 10, 10, 10 };
		Vector3int vecBint = { 40, 20, 30 };

		CHECK(Math::Lerp(vecAint, vecBint, 0) == Birb::Vector3int(10, 10, 10));
		CHECK(Math::Lerp(vecAint, vecBint, 0.5) == Birb::Vector3int(25, 15, 20));
		CHECK(Math::Lerp(vecAint, vecBint, 0.75) == Birb::Vector3int(33, 18, 25));
		CHECK(Math::Lerp(vecAint, vecBint, 1) == Birb::Vector3int(40, 20, 30));
	}

	TEST_CASE("Calculate the centerpoint between two 1D floats")
	{
		float a = 0;
		float b = 10;

		CHECK(Math::CenterPoint(a, b) == 5);
	}

	TEST_CASE("Calculate the centerpoint between two 2D float vectors")
	{
		Vector2f pointAf(1.0f, 1.0f);
		Vector2f pointBf(8.0f, 3.0f);

		Vector2f resultf = Birb::Math::CenterPoint(pointAf, pointBf);
		Vector2f expectedResult(4.5f, 2.0f);

		CHECK(resultf == expectedResult);
	}

	TEST_CASE("Calculate the centerpoint between two 2D integer vectors")
	{
		Vector2int pointAint(1, 1);
		Vector2int pointBint(8, 3);

		Vector2f resultint = Birb::Math::CenterPoint(pointAint, pointBint);
		Vector2f expectedResult(4.5f, 2.0f);

		CHECK(resultint == expectedResult);
	}

	TEST_CASE("Calculate the centerpoint between two 3D float vectors")
	{
		Vector3f pointAf(1.0f, 1.0f, 1.0f);
		Vector3f pointBf(8.0f, 3.0f, 2.0f);

		Vector3f resultf = Birb::Math::CenterPoint(pointAf, pointBf);
		Vector3f expectedResult(4.5f, 2.0f, 1.5f);

		CHECK(resultf == expectedResult);
	}

	TEST_CASE("Calculate the centerpoint between two 3D integer vectors")
	{
		Vector3int pointAint(1, 1, 1);
		Vector3int pointBint(8, 3, 2);

		Vector3f resultint = Birb::Math::CenterPoint(pointAint, pointBint);
		Vector3f expectedResult(4.5f, 2.0f, 1.5f);

		CHECK(resultint == expectedResult);
	}

	TEST_CASE("Find closest point to given point in a list of points")
	{
		Vector2int points[5] = {
			Vector2int(0, 0),
			Vector2int(3, 3),
			Vector2int(1, 1),
			Vector2int(8, 9),
			Vector2int(-5, 10),
		};

		std::vector<Vector2int> pointList;

		std::vector<Vector2int> ignoreList =
		{
			Vector2int(1, 1),
			Vector2int(3, 3)
		};

		pointList.insert(pointList.end(), points, points + 5);

		CHECK(Math::FindClosestPoint(points[0], points, 5) == Birb::Vector2int(1, 1));
		CHECK(Math::FindClosestPoint(pointList[0], pointList) == Birb::Vector2int(1, 1));
		CHECK(Math::FindClosestPoint(pointList[0], pointList, ignoreList) == Birb::Vector2int(-5, 10));
	}

	TEST_CASE("Rounding with specified accuracy")
	{
		double value1 = 0.013333333;
		float value2 = 0.017777777;

		CHECK(Math::Round(value1, 6) == 0.013333);
		CHECK(Math::Round(value1, 3) == 0.013);
		CHECK(Math::Round(value1, 2) == 0.01);

		CHECK(Math::Round(value2, 6) == 0.017778);
		CHECK(Math::Round(value2, 3) == 0.018);
		CHECK(Math::Round(value2, 2) == 0.02);
	}

	TEST_CASE("Is digit (float)")
	{
		float valueA = 0.5f;
		float valueB = 10.0f;
		float valueC = 1.4f;

		CHECK_FALSE(Math::IsDigit(valueA));
		CHECK(Math::IsDigit(valueB));
		CHECK_FALSE(Math::IsDigit(valueC));
	}

	TEST_CASE("Is digit (double)")
	{
		double valueA = 0.5f;
		double valueB = 10.0f;
		double valueC = 1.4f;

		CHECK_FALSE(Math::IsDigit(valueA));
		CHECK(Math::IsDigit(valueB));
		CHECK_FALSE(Math::IsDigit(valueC));
	}

	/* Data type tests */

	/* Vector2f */
	TEST_CASE("Default Vector2f")
	{
		Vector2f vector;
		CHECK(vector.x == 0);
		CHECK(vector.y == 0);
	}

	TEST_CASE("Vector2f with arguments")
	{
		CHECK(Vector2f(1, 4).x == 1);
		CHECK(Vector2f(1, 4).y == 4);
		CHECK(Vector2f(1.53f, 5.21f).x == 1.53f);
		CHECK(Vector2f(1.53f, 5.21f).y == 5.21f);
	}

	TEST_CASE("Vector2f operator overloads")
	{
		Vector2f vecA(1.0f, 1.5f);
		Vector2f vecB(2.0f, 3.2f);

		CHECK(vecA + vecB == Vector2f(3.0f, 4.7f));
		CHECK(vecA - vecB == Vector2f(-1.0f, -1.7f));
		CHECK(vecA * vecB == Vector2f(2.0f, 4.8f));
		CHECK(vecA / vecB == Vector2f(0.5f, 0.46875f));
	}

	/* Vector2int */
	TEST_CASE("Default Vector2int")
	{
		Vector2int vector;
		CHECK(vector.x == 0);
		CHECK(vector.y == 0);
	}

	TEST_CASE("Vector2int with arguments")
	{
		CHECK(Vector2int(1, 4).x == 1);
		CHECK(Vector2int(1, 4).y == 4);
		CHECK(Vector2int(1.53f, 5.21f).x == 2);
		CHECK(Vector2int(1.53f, 5.21f).y == 5);
	}

	TEST_CASE("Vector2int operator overloads")
	{
		Vector2int vecA(4, 2);
		Vector2int vecB(2, 3);

		CHECK(vecA + vecB == Vector2int(6, 5));
		CHECK(vecA - vecB == Vector2int(2, -1));
		CHECK(vecA * vecB == Vector2int(8, 6));
		CHECK(vecA / vecB == Vector2int(2, 1));
	}

	/* Vector3f */
	TEST_CASE("Default Vector3f")
	{
		Vector3f vector;
		CHECK(vector.x == 0);
		CHECK(vector.y == 0);
		CHECK(vector.z == 0);
	}

	TEST_CASE("Vector3f with arguments")
	{
		CHECK(Vector3f(1, 4, 2).x == 1);
		CHECK(Vector3f(1, 4, 2).y == 4);
		CHECK(Vector3f(1, 4, 2).z == 2);
		CHECK(Vector3f(1.53f, 5.21f, 2.45f).x == 1.53f);
		CHECK(Vector3f(1.53f, 5.21f, 2.45f).y == 5.21f);
		CHECK(Vector3f(1.53f, 5.21f, 2.45f).z == 2.45f);
	}

	TEST_CASE("Vector3f operator overloads")
	{
		Vector3f vecA(1.0f, 1.5f, 0.2f);
		Vector3f vecB(2.0f, 3.2f, 2.0f);

		CHECK(vecA + vecB == Vector3f(3.0f, 4.7f, 2.2f));
		CHECK(vecA - vecB == Vector3f(-1.0f, -1.7f, -1.8f));
		CHECK(vecA * vecB == Vector3f(2.0f, 4.8f, 0.4f));
		CHECK(vecA / vecB == Vector3f(0.5f, 0.468750f, 0.1f));
	}

	/* Vector3int */
	TEST_CASE("Default Vector3int")
	{
		Vector3int vector;
		CHECK(vector.x == 0);
		CHECK(vector.y == 0);
		CHECK(vector.z == 0);
	}

	TEST_CASE("Vector3int with arguments")
	{
		CHECK(Vector3int(1, 4, 2).x == 1);
		CHECK(Vector3int(1, 4, 2).y == 4);
		CHECK(Vector3int(1, 4, 2).z == 2);
		CHECK(Vector3int(1.53f, 5.21f, 2.45f).x == 2);
		CHECK(Vector3int(1.53f, 5.21f, 2.45f).y == 5);
		CHECK(Vector3int(1.53f, 5.21f, 2.45f).z == 2);
	}

	TEST_CASE("Vector3int operator overloads")
	{
		Vector3int vecA(4, 6, 5);
		Vector3int vecB(2, 3, 2);

		CHECK(vecA + vecB == Vector3int(6, 9, 7));
		CHECK(vecA - vecB == Vector3int(2, 3, 3));
		CHECK(vecA * vecB == Vector3int(8, 18, 10));
		CHECK(vecA / vecB == Vector3int(2, 2, 3));
	}

	TEST_CASE("Find highest and lowest double value")
	{
		double values[5] = 
		{
			4, 5, 1.6, 16.5, 3.6
		};

		std::vector<double> valuesVector = 
		{
			4, 5, 1.6, 16.5, 3.6
		};

		CHECK(Math::FindHighestValue(values, 5) == 16.5);
		CHECK(Math::FindLowestValue(values, 5) == 1.6);

		CHECK(Math::FindHighestValue(valuesVector) == 16.5);
		CHECK(Math::FindLowestValue(valuesVector) == 1.6);
	}

	TEST_CASE("Find highest and lowest float value")
	{
		float values[5] = 
		{
			4, 5, 1.6f, 16.5f, 3.6f
		};

		std::vector<float> valuesVector = 
		{
			4, 5, 1.6f, 16.5f, 3.6f
		};

		CHECK(Math::FindHighestValue(values, 5) == 16.5f);
		CHECK(Math::FindLowestValue(values, 5) == 1.6f);

		CHECK(Math::FindHighestValue(valuesVector) == 16.5f);
		CHECK(Math::FindLowestValue(valuesVector) == 1.6f);
	}

	TEST_CASE("Find highest and lowest int value")
	{
		int values[5] = 
		{
			4, 5, 1, 16, 7
		};

		std::vector<int> valuesVector = 
		{
			4, 5, 1, 16, 7
		};

		CHECK(Math::FindHighestValue(values, 5) == 16);
		CHECK(Math::FindLowestValue(values, 5) == 1);

		CHECK(Math::FindHighestValue(valuesVector) == 16);
		CHECK(Math::FindLowestValue(valuesVector) == 1);
	}

	TEST_CASE("Calculate average from double array")
	{
		double values[5] = 
		{
			4, 5, 1.6, 16.5, 3.6
		};

		CHECK(Math::Round(Math::Average(values, 5), 2) == 6.14);
	}

	TEST_CASE("Calculate average from float array")
	{
		float values[5] = 
		{
			4, 5, 1.6f, 16.5f, 3.6f
		};

		CHECK(Math::Round(Math::Average(values, 5), 2) == 6.14);
	}

	TEST_CASE("Calculate average from int array")
	{
		int values[5] = 
		{
			4, 5, 1, 16, 3
		};

		CHECK(Math::Round(Math::Average(values, 5), 2) == 5.8);
	}

	TEST_CASE("Normalize a value to set range")
	{
		double values[13] = {
			12, 19, 21, 23, 25, 35, 47, 48, 59, 65, 66, 67, 68
		};

		double lowestValue 	= Math::FindLowestValue(values, 13);
		double highestValue = Math::FindHighestValue(values, 13);
		double normalized_maximum = 100;

		CHECK(Math::Normalize(values[0], lowestValue, highestValue, normalized_maximum) == 0);
		CHECK(Math::Normalize(values[1], lowestValue, highestValue, normalized_maximum) == 12.5);
		CHECK(Math::Round(Math::Normalize(values[2], lowestValue, highestValue,normalized_maximum), 2) == 16.07);
		CHECK(Math::Round(Math::Normalize(values[11], lowestValue, highestValue, normalized_maximum), 2) == 98.21);
		CHECK(Math::Normalize(values[12], lowestValue, highestValue, normalized_maximum) == 100);
	}
}
