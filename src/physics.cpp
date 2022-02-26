#include "Physics.hpp"

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
	}
}
