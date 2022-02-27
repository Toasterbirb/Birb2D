#pragma once
#include <SDL2/SDL.h>
#include "Utils.hpp"
#include "Entity.hpp"

namespace Birb
{
	namespace Physics
	{
		bool RectCollision(const Rect& rectA, const Rect& rectB);
		bool RectCollision(const Birb::Rect rects[], const int& size);
		bool RectCollision(const std::vector<Birb::Rect>& rects);
		bool EntityCollision(const Entity& entityA, const Entity& entityB);
	}
}
