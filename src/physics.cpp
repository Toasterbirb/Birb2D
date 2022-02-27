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

		bool RectCollision(const Birb::Rect rects[], const int& size)
		{
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					if (i != j && RectCollision(rects[i], rects[j]))
						return true;
			return false;
		}

		bool RectCollision(const std::vector<Birb::Rect>& rects)
		{
			for (int i = 0; i < (int)rects.size(); i++)
				for (int j = 0; j < (int)rects.size(); j++)
					if (i != j && RectCollision(rects[i], rects[j]))
						return true;
			return false;
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
