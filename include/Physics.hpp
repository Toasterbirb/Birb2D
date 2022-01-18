#pragma once
#include <SDL2/SDL.h>
#include "Utils.hpp"
#include "Entity.hpp"

namespace Birb
{
	namespace Physics
	{
		bool RectCollision(Rect rectA, Rect rectB);
		bool EntityCollision(Entity entityA, Entity entityB);
	}
}
