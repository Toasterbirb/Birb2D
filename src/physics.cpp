#include "Physics.hpp"

namespace Birb
{
	namespace Physics
	{
		bool RectCollision(Rect rectA, Rect rectB)
		{
			SDL_Rect A = rectA.getSDLRect();
			SDL_Rect B = rectB.getSDLRect();
			return SDL_HasIntersection(&A, &B);
		}

		bool EntityCollision(Entity entityA, Entity entityB)
		{
			SDL_Rect A = entityA.rect.getSDLRect();
			SDL_Rect B = entityB.rect.getSDLRect();
			return SDL_HasIntersection(&A, &B);
		}
	}
}
