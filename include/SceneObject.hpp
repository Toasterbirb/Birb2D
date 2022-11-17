#pragma once

#include "Vector.hpp"

namespace Birb
{
	class SceneObject
	{
	public:
		SceneObject();
		SceneObject(const int& priority);
		SceneObject(const int& priority, const bool& active);
		int renderingPriority;
		bool sceneActive;
		bool active;
		bool world_space;
		float parallax_multiplier;

		virtual void RenderFunc() = 0;
		virtual void SetPos(const Vector2& delta) = 0;
	};
}
