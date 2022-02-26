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

		TEST_CASE("RectCollision")
		{
			Birb::Rect rectA(0, 0, 4, 2);
			Birb::Rect rectB(2, 1, 3, 2);
			Birb::Rect rectC(5, 1, 3, 2);

			CHECK(Birb::Physics::RectCollision(rectA, rectB));
			CHECK_FALSE(Birb::Physics::RectCollision(rectA, rectC));
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

		TEST_CASE("EntityCollision")
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

		TEST_CASE("EntityCollision with localScale")
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
