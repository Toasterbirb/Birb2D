#pragma once
#include <SDL2/SDL.h>
#include "Utils.hpp"
#include "Entity.hpp"

namespace Birb
{
	namespace Physics
	{
		bool RectCollision(const Rect& rectA, const Rect& rectB);
		bool EntityCollision(const Entity& entityA, const Entity& entityB);
	}
}
