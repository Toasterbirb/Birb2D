#pragma once

#include "Vector.hpp"

namespace Birb
{
	class SceneObject
	{
	public:
		SceneObject();
		SceneObject(const int& priority);
		int renderingPriority;
		bool sceneActive;
		virtual void RenderFunc() = 0;
		virtual void SetPos(const Vector2f& delta) = 0;
	};
}
