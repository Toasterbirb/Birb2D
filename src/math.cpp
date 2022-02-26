#include "Math.hpp"

namespace Birb
{
	float Math::VectorDistance(const Vector2f& a, const Vector2f& b)
	{
		return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
	}

	float Math::VectorDistance(const Vector2int& a, const Vector2int& b)
	{
		return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
	}

	TEST_CASE("Distance calculation with 2D vectors")
	{
		Birb::Vector2f pointAf(1.0f, 1.0f);
		Birb::Vector2f pointBf(8.0f, 3.0f);

		Birb::Vector2int pointAint(1, 1);
		Birb::Vector2int pointBint(8, 3);

		CHECK(Birb::Math::VectorDistance(pointAf, pointBf) == 7.2801098892805f);
		CHECK(Birb::Math::VectorDistance(pointAint, pointBint) == 7.2801098892805f);
	}

	float Math::VectorDistance(const Vector3f& a, const Vector3f& b)
	{
		return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2) + std::pow(b.z - a.z, 2));
	}

	float Math::VectorDistance(const Vector3int& a, const Vector3int& b)
	{
		return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2) + std::pow(b.z - a.z, 2));
	}

	TEST_CASE("Distance calculation with 3D vectors")
	{
		Birb::Vector3f pointAf(1.0f, 1.0f, 1.0f);
		Birb::Vector3f pointBf(8.0f, 3.0f, 2.0f);

		Birb::Vector3int pointAint(1, 1, 1);
		Birb::Vector3int pointBint(8, 3, 2);

		CHECK(std::roundf(Birb::Math::VectorDistance(pointAf, pointBf)) == std::roundf(7.3484792283495));
		CHECK(std::roundf(Birb::Math::VectorDistance(pointAint, pointBint)) == std::roundf(7.3484692283495));
	}

	float Math::Clamp(const float& value, const float& min, const float& max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;

		return value;
	}

	TEST_CASE("float clamping")
	{
		float floatvalue = 15;

		CHECK(Birb::Math::Clamp(floatvalue, 0.0f, 5.0f) == 5.0f);
		CHECK(Birb::Math::Clamp(floatvalue, 0.0f, 20.0f) == 15.0f);
		CHECK(Birb::Math::Clamp(floatvalue, 20.0f, 40.0f) == 20.0f);
		CHECK(Birb::Math::Clamp(floatvalue, 40.0f, 5.0f) == 40.0f);
	}

	double Math::Clamp(const double& value, const double& min, const double& max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;

		return value;
	}

	TEST_CASE("double clamping")
	{
		double doublevalue = 20;

		CHECK(Birb::Math::Clamp(doublevalue, 0.0, 5.0) == 5.0);
		CHECK(Birb::Math::Clamp(doublevalue, 0.0, 25.0) == 20.0);
		CHECK(Birb::Math::Clamp(doublevalue, 25.0, 40.0) == 25.0);
		CHECK(Birb::Math::Clamp(doublevalue, 40.0, 5.0) == 40);
	}

	int Math::Clamp(const int& value, const int& min, const int& max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;

		return value;
	}

	TEST_CASE("integer clamping")
	{
		int intvalue = 10;

		CHECK(Birb::Math::Clamp(intvalue, 0, 5) == 5);
		CHECK(Birb::Math::Clamp(intvalue, 0, 20) == 10);
		CHECK(Birb::Math::Clamp(intvalue, 20, 40) == 20);
		CHECK(Birb::Math::Clamp(intvalue, 40, 5) == 40);
	}

	int Math::Lerp(const int& a, const int& b, const float& t)
	{
		return std::round(a + (b - a) * Clamp(t, 0.0f, 1.0f));
	}

	TEST_CASE("Lerping / interpolation with integers")
	{
		int a = 1;
		int b = 10;

		CHECK(Birb::Math::Lerp(a, b, 0) == 1);
		CHECK(Birb::Math::Lerp(a, b, 0.5) == 6);
		CHECK(Birb::Math::Lerp(a, b, 0.75) == 8);
		CHECK(Birb::Math::Lerp(a, b, 1) == 10);
	}
	
	float Math::Lerp(const float& a, const float& b, const float& t)
	{
		return (a + (b - a) * Clamp(t, 0.0f, 1.0f));
	}

	TEST_CASE("Lerping / interpolation with floats")
	{
		float a = 1;
		float b = 3;

		CHECK(Birb::Math::Lerp(a, b, 0) == 1);
		CHECK(Birb::Math::Lerp(a, b, 0.25) == 1.5f);
		CHECK(Birb::Math::Lerp(a, b, 0.5) == 2);
		CHECK(Birb::Math::Lerp(a, b, 1) == 3);
	}

	Vector2f Math::Lerp(const Vector2f& a, const Vector2f& b, const float& t)
	{
		return Vector2f(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t));
	}

	TEST_CASE("Lerping / interpolation with 2D float vectors")
	{
		Birb::Vector2f vecAf = { 1.0f, 1.0f };
		Birb::Vector2f vecBf = { 4.0f, 2.0f };

		CHECK(Birb::Math::Lerp(vecAf, vecBf, 0) == Birb::Vector2f(1, 1));
		CHECK(Birb::Math::Lerp(vecAf, vecBf, 0.5) == Birb::Vector2f(2.5, 1.5));
		CHECK(Birb::Math::Lerp(vecAf, vecBf, 0.75) == Birb::Vector2f(3.25, 1.75));
		CHECK(Birb::Math::Lerp(vecAf, vecBf, 1) == Birb::Vector2f(4, 2));
	}

	Vector2int Math::Lerp(const Vector2int& a, const Vector2int& b, const float& t)
	{
		return Vector2int(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t));
	}

	TEST_CASE("Lerping / interpolation with 2D integer vectors")
	{
		Birb::Vector2int vecAint = { 10, 10 };
		Birb::Vector2int vecBint = { 40, 20 };

		CHECK(Birb::Math::Lerp(vecAint, vecBint, 0) == Birb::Vector2int(10, 10));
		CHECK(Birb::Math::Lerp(vecAint, vecBint, 0.5) == Birb::Vector2int(25, 15));
		CHECK(Birb::Math::Lerp(vecAint, vecBint, 0.75) == Birb::Vector2int(33, 18));
		CHECK(Birb::Math::Lerp(vecAint, vecBint, 1) == Birb::Vector2int(40, 20));
	}

	Vector3f Math::Lerp(const Vector3f& a, const Vector3f& b, const float& t)
	{
		return Vector3f(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t), Lerp(a.z, b.z, t));
	}

	TEST_CASE("Lerping / interpolation with 3D float vectors")
	{
		Birb::Vector3f vecAf = { 1.0f, 1.0f, 1.0f };
		Birb::Vector3f vecBf = { 4.0f, 2.0f, 3.0f };

		CHECK(Birb::Math::Lerp(vecAf, vecBf, 0) == Birb::Vector3f(1, 1, 1));
		CHECK(Birb::Math::Lerp(vecAf, vecBf, 0.5) == Birb::Vector3f(2.5, 1.5, 2));
		CHECK(Birb::Math::Lerp(vecAf, vecBf, 0.75) == Birb::Vector3f(3.25, 1.75, 2.5));
		CHECK(Birb::Math::Lerp(vecAf, vecBf, 1) == Birb::Vector3f(4, 2, 3));
	}

	Vector3int Math::Lerp(const Vector3int& a, const Vector3int& b, const float& t)
	{
		return Vector3int(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t), Lerp(a.z, b.z, t));
	}

	TEST_CASE("Lerping / interpolation with 3D integer vectors")
	{
		Birb::Vector3int vecAint = { 10, 10, 10 };
		Birb::Vector3int vecBint = { 40, 20, 30 };

		CHECK(Birb::Math::Lerp(vecAint, vecBint, 0) == Birb::Vector3int(10, 10, 10));
		CHECK(Birb::Math::Lerp(vecAint, vecBint, 0.5) == Birb::Vector3int(25, 15, 20));
		CHECK(Birb::Math::Lerp(vecAint, vecBint, 0.75) == Birb::Vector3int(33, 18, 25));
		CHECK(Birb::Math::Lerp(vecAint, vecBint, 1) == Birb::Vector3int(40, 20, 30));
	}


	float Math::CenterPoint(const float& a, const float& b)
	{
		return (a + b) / 2;
	}

	TEST_CASE("Calculate the centerpoint between two 1D floats")
	{
		float a = 0;
		float b = 10;

		CHECK(Birb::Math::CenterPoint(a, b) == 5);
	}

	Vector2f Math::CenterPoint(const Vector2f& a, const Vector2f& b)
	{
		return Vector2f(CenterPoint(a.x, b.x), CenterPoint(a.y, b.y));
	}

	TEST_CASE("Calculate the centerpoint between two 2D float vectors")
	{
		Birb::Vector2f pointAf(1.0f, 1.0f);
		Birb::Vector2f pointBf(8.0f, 3.0f);

		Birb::Vector2f resultf = Birb::Math::CenterPoint(pointAf, pointBf);
		Birb::Vector2f expectedResult(4.5f, 2.0f);

		CHECK(resultf == expectedResult);
	}

	Vector2f Math::CenterPoint(const Vector2int& a, const Vector2int& b)
	{
		return Vector2f(CenterPoint(a.x, b.x), CenterPoint(a.y, b.y));
	}

	TEST_CASE("Calculate the centerpoint between two 2D integer vectors")
	{
		Birb::Vector2int pointAint(1, 1);
		Birb::Vector2int pointBint(8, 3);

		Birb::Vector2f resultint = Birb::Math::CenterPoint(pointAint, pointBint);
		Birb::Vector2f expectedResult(4.5f, 2.0f);

		CHECK(resultint == expectedResult);
	}

	Vector3f Math::CenterPoint(const Vector3f& a, const Vector3f& b)
	{
		return Vector3f(CenterPoint(a.x, b.x), CenterPoint(a.y, b.y), CenterPoint(a.z, b.z));
	}

	TEST_CASE("Calculate the centerpoint between two 3D float vectors")
	{
		Birb::Vector3f pointAf(1.0f, 1.0f, 1.0f);
		Birb::Vector3f pointBf(8.0f, 3.0f, 2.0f);

		Birb::Vector3f resultf = Birb::Math::CenterPoint(pointAf, pointBf);
		Birb::Vector3f expectedResult(4.5f, 2.0f, 1.5f);

		CHECK(resultf == expectedResult);
	}

	Vector3f Math::CenterPoint(const Vector3int& a, const Vector3int& b)
	{
		return Vector3f(CenterPoint(a.x, b.x), CenterPoint(a.y, b.y), CenterPoint(a.z, b.z));
	}

	TEST_CASE("Calculate the centerpoint between two 3D integer vectors")
	{
		Birb::Vector3int pointAint(1, 1, 1);
		Birb::Vector3int pointBint(8, 3, 2);

		Birb::Vector3f resultint = Birb::Math::CenterPoint(pointAint, pointBint);
		Birb::Vector3f expectedResult(4.5f, 2.0f, 1.5f);

		CHECK(resultint == expectedResult);
	}

	Vector2int Math::FindClosestPoint(const Vector2int& point, Vector2int points[], const int& pointCount)
	{
		Vector2int currentClosestPoint = points[0];
		float currentClosestDistance = VectorDistance(point, points[0]);

		for (int i = 1; i < pointCount; i++)
		{
			float distance = VectorDistance(point, points[i]);

			/* Compare the distance to the current shortest one. Also set a new closest point if the previous one 
			 * was in the exact same position */
			if (distance <= currentClosestDistance || currentClosestDistance == 0.0f)
			{
				currentClosestPoint = points[i];
				currentClosestDistance = distance;
			}
		}
		return currentClosestPoint;
	}

	Vector2int Math::FindClosestPoint(const Vector2int& point, const std::vector<Vector2int>& points)
	{
		Vector2int currentClosestPoint = points[0];
		float currentClosestDistance = VectorDistance(point, points[0]);

		for (int i = 1; i < (int)points.size(); i++)
		{
			float distance = VectorDistance(point, points[i]);

			/* Compare the distance to the current shortest one. Also set a new closest point if the previous one 
			 * was in the exact same position */
			if (distance <= currentClosestDistance || currentClosestDistance == 0.0f)
			{
				currentClosestPoint = points[i];
				currentClosestDistance = distance;
			}
		}
		return currentClosestPoint;
	}


	Vector2int Math::FindClosestPoint(const Vector2int& point, const std::vector<Vector2int>& points, const std::vector<Vector2int>& ignoredPoints)
	{
		/* Find the first non-ignored point */
		Vector2int firstNotIgnored;
		for (int i = 0; i < (int)points.size(); i++)
		{
			bool ignored = false;
			for (int j = 0; j < (int)ignoredPoints.size(); j++)
			{
				if (points[i] == ignoredPoints[j])
				{
					ignored = true;
					break;
				}
			}

			if (!ignored)
			{
				firstNotIgnored = points[i];
				break;
			}
		}

		Vector2int currentClosestPoint = firstNotIgnored;
		float currentClosestDistance = VectorDistance(point, points[0]);

		bool ignore;
		for (int i = 1; i < (int)points.size(); i++)
		{
			ignore = false;

			/* Check if the point is in the ignore list */
			for (int j = 0; j < (int)ignoredPoints.size(); j++)
				if (points[i] == ignoredPoints[j])
				{
					ignore = true;
					break;
				}

			if (!ignore)
			{
				float distance = VectorDistance(point, points[i]);

				/* Compare the distance to the current shortest one. Also set a new closest point if the previous one 
				 * was in the exact same position */
				if (distance <= currentClosestDistance || currentClosestDistance == 0.0f)
				{
					currentClosestPoint = points[i];
					currentClosestDistance = distance;
				}
			}
		}
		return currentClosestPoint;
	}

	TEST_CASE("Find closest point to given point in a list of points")
	{
		Birb::Vector2int points[5] = {
			Birb::Vector2int(0, 0),
			Birb::Vector2int(3, 3),
			Birb::Vector2int(1, 1),
			Birb::Vector2int(8, 9),
			Birb::Vector2int(-5, 10),
		};

		std::vector<Birb::Vector2int> pointList;

		std::vector<Birb::Vector2int> ignoreList =
		{
			Birb::Vector2int(1, 1),
			Birb::Vector2int(3, 3)
		};

		pointList.insert(pointList.end(), points, points + 5);

		CHECK(Birb::Math::FindClosestPoint(points[0], points, 5) == Birb::Vector2int(1, 1));
		CHECK(Birb::Math::FindClosestPoint(pointList[0], pointList) == Birb::Vector2int(1, 1));
		CHECK(Birb::Math::FindClosestPoint(pointList[0], pointList, ignoreList) == Birb::Vector2int(-5, 10));
	}

	double Math::Round(const double& value, const int& decimal_points)
	{
		/* How this thing works: 
		 * 1. Multiply the value with 10 ^ decimal points. This will leave the needed values before the decimal point
		 * 2. Round to integer
		 * 3. Divide the value with 10 ^ decimal points to get the desired rounded decimal value
		 * */
		return std::round(value * std::pow(10, decimal_points)) / std::pow(10, decimal_points);
	}

	TEST_CASE("Rounding with specified accuracy")
	{
		double value1 = 0.013333333;
		float value2 = 0.017777777;

		CHECK(Birb::Math::Round(value1, 6) == 0.013333);
		CHECK(Birb::Math::Round(value1, 3) == 0.013);
		CHECK(Birb::Math::Round(value1, 2) == 0.01);

		CHECK(Birb::Math::Round(value2, 6) == 0.017778);
		CHECK(Birb::Math::Round(value2, 3) == 0.018);
		CHECK(Birb::Math::Round(value2, 2) == 0.02);
	}
}

/* Data type tests */

/* Vector2f */
TEST_CASE("Default Vector2f")
{
    Birb::Vector2f vector;
    CHECK(vector.x == 0);
    CHECK(vector.y == 0);
}

TEST_CASE("Vector2f with arguments")
{
    CHECK(Birb::Vector2f(1, 4).x == 1);
    CHECK(Birb::Vector2f(1, 4).y == 4);
    CHECK(Birb::Vector2f(1.53f, 5.21f).x == 1.53f);
    CHECK(Birb::Vector2f(1.53f, 5.21f).y == 5.21f);
}

TEST_CASE("Vector2f operator overloads")
{
	Birb::Vector2f vecA(1.0f, 1.5f);
	Birb::Vector2f vecB(2.0f, 3.2f);

	CHECK(vecA + vecB == Birb::Vector2f(3.0f, 4.7f));
	CHECK(vecA - vecB == Birb::Vector2f(-1.0f, -1.7f));
	CHECK(vecA * vecB == Birb::Vector2f(2.0f, 4.8f));
	CHECK(vecA / vecB == Birb::Vector2f(0.5f, 0.46875f));
}

/* Vector2int */
TEST_CASE("Default Vector2int")
{
    Birb::Vector2int vector;
    CHECK(vector.x == 0);
    CHECK(vector.y == 0);
}

TEST_CASE("Vector2int with arguments")
{
    CHECK(Birb::Vector2int(1, 4).x == 1);
    CHECK(Birb::Vector2int(1, 4).y == 4);
    CHECK(Birb::Vector2int(1.53f, 5.21f).x == 2);
    CHECK(Birb::Vector2int(1.53f, 5.21f).y == 5);
}

TEST_CASE("Vector2int operator overloads")
{
	Birb::Vector2int vecA(4, 2);
	Birb::Vector2int vecB(2, 3);

	CHECK(vecA + vecB == Birb::Vector2int(6, 5));
	CHECK(vecA - vecB == Birb::Vector2int(2, -1));
	CHECK(vecA * vecB == Birb::Vector2int(8, 6));
	CHECK(vecA / vecB == Birb::Vector2int(2, 1));
}

/* Vector3f */
TEST_CASE("Default Vector3f")
{
	Birb::Vector3f vector;
    CHECK(vector.x == 0);
    CHECK(vector.y == 0);
    CHECK(vector.z == 0);
}

TEST_CASE("Vector3f with arguments")
{
    CHECK(Birb::Vector3f(1, 4, 2).x == 1);
    CHECK(Birb::Vector3f(1, 4, 2).y == 4);
    CHECK(Birb::Vector3f(1, 4, 2).z == 2);
    CHECK(Birb::Vector3f(1.53f, 5.21f, 2.45f).x == 1.53f);
    CHECK(Birb::Vector3f(1.53f, 5.21f, 2.45f).y == 5.21f);
    CHECK(Birb::Vector3f(1.53f, 5.21f, 2.45f).z == 2.45f);
}

TEST_CASE("Vector3f operator overloads")
{
	Birb::Vector3f vecA(1.0f, 1.5f, 0.2f);
	Birb::Vector3f vecB(2.0f, 3.2f, 2.0f);

	CHECK(vecA + vecB == Birb::Vector3f(3.0f, 4.7f, 2.2f));
	CHECK(vecA - vecB == Birb::Vector3f(-1.0f, -1.7f, -1.8f));
	CHECK(vecA * vecB == Birb::Vector3f(2.0f, 4.8f, 0.4f));
	CHECK(vecA / vecB == Birb::Vector3f(0.5f, 0.468750f, 0.1f));
}

/* Vector3int */
TEST_CASE("Default Vector3int")
{
	Birb::Vector3int vector;
    CHECK(vector.x == 0);
    CHECK(vector.y == 0);
    CHECK(vector.z == 0);
}

TEST_CASE("Vector3int with arguments")
{
    CHECK(Birb::Vector3int(1, 4, 2).x == 1);
    CHECK(Birb::Vector3int(1, 4, 2).y == 4);
    CHECK(Birb::Vector3int(1, 4, 2).z == 2);
    CHECK(Birb::Vector3int(1.53f, 5.21f, 2.45f).x == 2);
    CHECK(Birb::Vector3int(1.53f, 5.21f, 2.45f).y == 5);
    CHECK(Birb::Vector3int(1.53f, 5.21f, 2.45f).z == 2);
}

TEST_CASE("Vector3int operator overloads")
{
	Birb::Vector3int vecA(4, 6, 5);
	Birb::Vector3int vecB(2, 3, 2);

	CHECK(vecA + vecB == Birb::Vector3int(6, 9, 7));
	CHECK(vecA - vecB == Birb::Vector3int(2, 3, 3));
	CHECK(vecA * vecB == Birb::Vector3int(8, 18, 10));
	CHECK(vecA / vecB == Birb::Vector3int(2, 2, 3));
}
