#include "Physics.hpp"
#include "doctest.h"


namespace Birb
{
	namespace Physics
	{
		TEST_CASE("Rect collision")
		{
			Rect rectA(0, 0, 4, 2);
			Rect rectB(2, 1, 3, 2);
			Rect rectC(5, 1, 3, 2);

			CHECK(RectCollision(rectA, rectB));
			CHECK_FALSE(RectCollision(rectA, rectC));
		}

		TEST_CASE("Rect collision with multiple rects at once in an array")
		{
			Rect rectsA[3] = {
				Rect(0, 0, 4, 2),
				Rect(2, 1, 3, 2),
				Rect(5, 1, 3, 2),
			};

			Rect rectsB[3] = {
				Rect(0, 0, 4, 2),
				Rect(200, 1, 3, 2),
				Rect(5, 100, 3, 2),
			};

			CHECK(RectCollision(rectsA, 3));
			CHECK_FALSE(RectCollision(rectsB, 3));
		}

		TEST_CASE("Rect collision with multiple rects at once in a list")
		{
			std::vector<Rect> rectsA = {
				Rect(0, 0, 4, 2),
				Rect(2, 1, 3, 2),
				Rect(5, 1, 3, 2),
			};

			std::vector<Rect> rectsB = {
				Rect(0, 0, 4, 2),
				Rect(200, 1, 3, 2),
				Rect(5, 100, 3, 2),
			};

			CHECK(RectCollision(rectsA));
			CHECK_FALSE(RectCollision(rectsB));
		}

		TEST_CASE("Entity collision")
		{
			Entity entityA("Entity A");
			Entity entityB("Entity B");
			Entity entityC("Entity C");

			Rect rectA(0, 0, 4, 2);
			entityA.rect = rectA;

			Rect rectB(2, 1, 3, 2);
			entityB.rect = rectB;

			Rect rectC(5, 1, 3, 2);
			entityC.rect = rectC;

			CHECK(EntityCollision(entityA, entityB));
			CHECK_FALSE(EntityCollision(entityA, entityC));
		}

		TEST_CASE("Entity collision with localScale")
		{
			Entity entityA("Entity A");
			Entity entityB("Entity B");

			Rect rectA(0, 0, 4, 2);
			entityA.rect = rectA;
			entityA.localScale = Vector2f(2, 1);

			Rect rectB(5, 1, 3, 2);
			entityB.rect = rectB;

			CHECK(EntityCollision(entityA, entityB));
		}
	}
}
