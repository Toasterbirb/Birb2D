#include "Physics.hpp"
#include "doctest.h"

namespace Birb
{
	namespace Physics
	{
		bool RectCollision(const Rect& rectA, const Rect& rectB)
		{
			SDL_Rect A = rectA.getSDLRect();
			SDL_Rect B = rectB.getSDLRect();

			return SDL_HasIntersection(&A, &B);
		}

		TEST_CASE("Rect collision")
		{
			Birb::Rect rectA(0, 0, 4, 2);
			Birb::Rect rectB(2, 1, 3, 2);
			Birb::Rect rectC(5, 1, 3, 2);

			CHECK(Birb::Physics::RectCollision(rectA, rectB));
			CHECK_FALSE(Birb::Physics::RectCollision(rectA, rectC));
		}

		bool RectCollision(const Birb::Rect rects[], const int& size)
		{
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					if (i != j && RectCollision(rects[i], rects[j]))
						return true;
			return false;
		}

		TEST_CASE("Rect collision with multiple rects at once in an array")
		{
			Birb::Rect rectsA[3] = {
				Birb::Rect(0, 0, 4, 2),
				Birb::Rect(2, 1, 3, 2),
				Birb::Rect(5, 1, 3, 2),
			};

			Birb::Rect rectsB[3] = {
				Birb::Rect(0, 0, 4, 2),
				Birb::Rect(200, 1, 3, 2),
				Birb::Rect(5, 100, 3, 2),
			};

			CHECK(RectCollision(rectsA, 3));
			CHECK_FALSE(RectCollision(rectsB, 3));
		}

		bool RectCollision(const std::vector<Birb::Rect>& rects)
		{
			for (int i = 0; i < (int)rects.size(); i++)
				for (int j = 0; j < (int)rects.size(); j++)
					if (i != j && RectCollision(rects[i], rects[j]))
						return true;
			return false;
		}

		TEST_CASE("Rect collision with multiple rects at once in a list")
		{
			std::vector<Birb::Rect> rectsA = {
				Birb::Rect(0, 0, 4, 2),
				Birb::Rect(2, 1, 3, 2),
				Birb::Rect(5, 1, 3, 2),
			};

			std::vector<Birb::Rect> rectsB = {
				Birb::Rect(0, 0, 4, 2),
				Birb::Rect(200, 1, 3, 2),
				Birb::Rect(5, 100, 3, 2),
			};

			CHECK(RectCollision(rectsA));
			CHECK_FALSE(RectCollision(rectsB));
		}

		bool EntityCollision(const Entity& entityA, const Entity& entityB)
		{
			SDL_Rect A = entityA.rect.getSDLRect();
			SDL_Rect B = entityB.rect.getSDLRect();

			/* Take localscale into account */
			A.w *= entityA.localScale.x;
			A.h *= entityA.localScale.y;
			B.w *= entityB.localScale.x;
			B.h *= entityB.localScale.y;

			return SDL_HasIntersection(&A, &B);
		}

		TEST_CASE("Entity collision")
		{
			Birb::Entity entityA("Entity A");
			Birb::Entity entityB("Entity B");
			Birb::Entity entityC("Entity C");

			Birb::Rect rectA(0, 0, 4, 2);
			entityA.rect = rectA;

			Birb::Rect rectB(2, 1, 3, 2);
			entityB.rect = rectB;

			Birb::Rect rectC(5, 1, 3, 2);
			entityC.rect = rectC;

			CHECK(Birb::Physics::EntityCollision(entityA, entityB));
			CHECK_FALSE(Birb::Physics::EntityCollision(entityA, entityC));
		}

		TEST_CASE("Entity collision with localScale")
		{
			Birb::Entity entityA("Entity A");
			Birb::Entity entityB("Entity B");

			Birb::Rect rectA(0, 0, 4, 2);
			entityA.rect = rectA;
			entityA.localScale = Birb::Vector2f(2, 1);

			Birb::Rect rectB(5, 1, 3, 2);
			entityB.rect = rectB;

			CHECK(Birb::Physics::EntityCollision(entityA, entityB));
		}
	}
}
