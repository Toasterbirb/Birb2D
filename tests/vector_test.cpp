#include "doctest.h"
#include "Vector.hpp"

namespace Birb
{
	TEST_CASE("Vector conversions")
	{
		Vector2 point2f(1.10f, 1.10f);
		Vector2Int point2int(1, 1);
		Vector3 point3f(1.10f, 1.10f, 2.10f);
		Vector3Int point3int(1, 1, 2);

		SUBCASE("To string")
		{
			CHECK(point2f.ToString() == "(1.1, 1.1)");
			CHECK(point2int.ToString() == "(1, 1)");
			CHECK(point3f.ToString() == "(1.1, 1.1, 2.1)");
			CHECK(point3int.ToString() == "(1, 1, 2)");
		}

		SUBCASE("To int vector")
		{
			CHECK(point2f.ToInt() == Vector2Int(1, 1));
			CHECK(point3f.ToInt() == Vector3Int(1, 1, 2));
		}

		SUBCASE("To float vector")
		{
			CHECK(point2int.ToFloat() == Vector2(1.0f, 1.0f));
			CHECK(point3int.ToFloat() == Vector3(1.0f, 1.0f, 2.0f));
		}
	}

	TEST_CASE("Default Vector2")
	{
		Vector2 vector;
		CHECK(vector.x == 0);
		CHECK(vector.y == 0);
	}

	TEST_CASE("Vector2 with arguments")
	{
		Vector2 vecA(1, 4);
		CHECK(vecA.x == 1);
		CHECK(vecA.y == 4);

		Vector2 vecB(1.53f, 5.21f);
		CHECK(vecB.x == 1.53f);
		CHECK(vecB.y == 5.21f);

		Vector2 vecC({2.2f, 5.1f});
		CHECK(vecC.x == 2.2f);
		CHECK(vecC.y == 5.1f);
	}

	TEST_CASE("Vector2 operator overloads")
	{
		Vector2 vecA(1.0f, 1.5f);
		Vector2 vecB(2.0f, 3.2f);
		Vector2 vecC(1.0f, 2.0f);
		Vector2 vecD(1.0f, 1.5f);

		CHECK(vecA + vecB == Vector2(3.0f, 4.7f));
		CHECK(vecA - vecB == Vector2(-1.0f, -1.7f));
		CHECK(vecA * vecB == Vector2(2.0f, 4.8f));
		CHECK(vecA / vecB == Vector2(0.5f, 0.46875f));

	    CHECK(vecD * 2  == Vector2(2.0f, 3.0f));
		CHECK(vecD / 2  == Vector2(0.5f, 0.75f));

		CHECK(vecA == vecA);
		CHECK(vecA != vecB);
		CHECK(vecA != vecC);
	}

	/* Vector2Int */
	TEST_CASE("Default Vector2Int")
	{
		Vector2Int vector;
		CHECK(vector.x == 0);
		CHECK(vector.y == 0);
	}

	TEST_CASE("Vector2Int with arguments")
	{
		Vector2Int vecA(1, 4);
		CHECK(vecA.x == 1);
		CHECK(vecA.y == 4);

		Vector2Int vecB(1.53f, 5.21f);
		CHECK(vecB.x == 2);
		CHECK(vecB.y == 5);

		Vector2Int vecC({2.2f, 5.1f});
		CHECK(vecC.x == 2);
		CHECK(vecC.y == 5);
	}

	TEST_CASE("Vector2Int operator overloads")
	{
		Vector2Int vecA(4, 2);
		Vector2Int vecB(2, 3);
		Vector2Int vecC(4, 3);
		Vector2Int vecD(2, 2);

		CHECK(vecA + vecB == Vector2Int(6, 5));
		CHECK(vecA - vecB == Vector2Int(2, -1));
		CHECK(vecA * vecB == Vector2Int(8, 6));
		CHECK(vecA / vecB == Vector2Int(2, 1));

		CHECK(vecD * 2  == Vector2Int(4, 4));
		CHECK(vecD / 2  == Vector2Int(1, 1));

		CHECK(vecA == vecA);
		CHECK(vecA != vecB);
		CHECK(vecA != vecC);
	}

	/* Vector3 */
	TEST_CASE("Default Vector3")
	{
		Vector3 vector;
		CHECK(vector.x == 0);
		CHECK(vector.y == 0);
		CHECK(vector.z == 0);
	}

	TEST_CASE("Vector3 with arguments")
	{
		Vector3 vecA(1, 4, 3);
		CHECK(vecA.x == 1);
		CHECK(vecA.y == 4);
		CHECK(vecA.z == 3);

		Vector3 vecB(1.53f, 5.21f, 3.5f);
		CHECK(vecB.x == 1.53f);
		CHECK(vecB.y == 5.21f);
		CHECK(vecB.z == 3.5f);

		Vector3 vecC({2.2f, 5.1f, 8.08f});
		CHECK(vecC.x == 2.2f);
		CHECK(vecC.y == 5.1f);
		CHECK(vecC.z == 8.08f);
	}

	TEST_CASE("Vector3 operator overloads")
	{
		Vector3 vecA(1.0f, 1.5f, 0.2f);
		Vector3 vecB(2.0f, 3.2f, 2.0f);
		Vector3 vecC(1.0f, 2.5f, 0.2f);
		Vector3 vecD(1.0f, 1.5f, 2.0f);

		CHECK(vecA + vecB == Vector3(3.0f, 4.7f, 2.2f));
		CHECK(vecA - vecB == Vector3(-1.0f, -1.7f, -1.8f));
		CHECK(vecA * vecB == Vector3(2.0f, 4.8f, 0.4f));
		CHECK(vecA / vecB == Vector3(0.5f, 0.468750f, 0.1f));

	    CHECK(vecD * 2  == Vector3(2.0f, 3.0f, 4.0f));
		CHECK(vecD / 2  == Vector3(0.5f, 0.75f, 1.0f));

		CHECK(vecA == vecA);
		CHECK(vecA != vecB);
		CHECK(vecA != vecC);
	}

	/* Vector3Int */
	TEST_CASE("Default Vector3Int")
	{
		Vector3Int vector;
		CHECK(vector.x == 0);
		CHECK(vector.y == 0);
		CHECK(vector.z == 0);
	}

	TEST_CASE("Vector3Int with arguments")
	{
		Vector3Int vecA(1, 4, 3);
		CHECK(vecA.x == 1);
		CHECK(vecA.y == 4);
		CHECK(vecA.z == 3);

		Vector3Int vecB(1.53f, 5.21f, 3.5f);
		CHECK(vecB.x == 2);
		CHECK(vecB.y == 5);
		CHECK(vecB.z == 4);

		Vector3Int vecC({2.2f, 5.1f, 8.08f});
		CHECK(vecC.x == 2);
		CHECK(vecC.y == 5);
		CHECK(vecC.z == 8);
	}

	TEST_CASE("Vector3Int operator overloads")
	{
		Vector3Int vecA(4, 6, 5);
		Vector3Int vecB(2, 3, 2);
		Vector3Int vecC(4, 7, 5);
		Vector3Int vecD(2, 2, 2);

		CHECK(vecA + vecB == Vector3Int(6, 9, 7));
		CHECK(vecA - vecB == Vector3Int(2, 3, 3));
		CHECK(vecA * vecB == Vector3Int(8, 18, 10));
		CHECK(vecA / vecB == Vector3Int(2, 2, 3));

		CHECK(vecD * 2  == Vector3Int(4, 4, 4));
		CHECK(vecD / 2  == Vector3Int(1, 1, 1));

		CHECK(vecA == vecA);
		CHECK(vecA != vecB);
		CHECK(vecA != vecC);
	}
}
