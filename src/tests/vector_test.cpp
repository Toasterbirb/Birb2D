#include "doctest.h"
#include "Vector.hpp"

namespace Birb
{
	TEST_CASE("Vector to string")
	{
		Vector2f point2f(1.10f, 1.10f);
		Vector2int point2int(1, 1);
		Vector3f point3f(1.10f, 1.10f, 2.10f);
		Vector3int point3int(1, 1, 2);

		CHECK(point2f.toString() == "(1.1, 1.1)");
		CHECK(point2int.toString() == "(1, 1)");
		CHECK(point3f.toString() == "(1.1, 1.1, 2.1)");
		CHECK(point3int.toString() == "(1, 1, 2)");
	}

	TEST_CASE("Default Vector2f")
	{
		Vector2f vector;
		CHECK(vector.x == 0);
		CHECK(vector.y == 0);
	}

	TEST_CASE("Vector2f with arguments")
	{
		Vector2f vecA(1, 4);
		CHECK(vecA.x == 1);
		CHECK(vecA.y == 4);

		Vector2f vecB(1.53f, 5.21f);
		CHECK(vecB.x == 1.53f);
		CHECK(vecB.y == 5.21f);

		Vector2f vecC({2.2f, 5.1f});
		CHECK(vecC.x == 2.2f);
		CHECK(vecC.y == 5.1f);
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
		Vector2int vecA(1, 4);
		CHECK(vecA.x == 1);
		CHECK(vecA.y == 4);

		Vector2int vecB(1.53f, 5.21f);
		CHECK(vecB.x == 2);
		CHECK(vecB.y == 5);

		Vector2int vecC({2.2f, 5.1f});
		CHECK(vecC.x == 2);
		CHECK(vecC.y == 5);
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
		Vector3f vecA(1, 4, 3);
		CHECK(vecA.x == 1);
		CHECK(vecA.y == 4);
		CHECK(vecA.z == 3);

		Vector3f vecB(1.53f, 5.21f, 3.5f);
		CHECK(vecB.x == 1.53f);
		CHECK(vecB.y == 5.21f);
		CHECK(vecB.z == 3.5f);

		Vector3f vecC({2.2f, 5.1f, 8.08f});
		CHECK(vecC.x == 2.2f);
		CHECK(vecC.y == 5.1f);
		CHECK(vecC.z == 8.08f);
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
		Vector3int vecA(1, 4, 3);
		CHECK(vecA.x == 1);
		CHECK(vecA.y == 4);
		CHECK(vecA.z == 3);

		Vector3int vecB(1.53f, 5.21f, 3.5f);
		CHECK(vecB.x == 2);
		CHECK(vecB.y == 5);
		CHECK(vecB.z == 4);

		Vector3int vecC({2.2f, 5.1f, 8.08f});
		CHECK(vecC.x == 2);
		CHECK(vecC.y == 5);
		CHECK(vecC.z == 8);
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
}
