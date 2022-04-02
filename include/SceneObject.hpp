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
			virtual void RenderFunc() = 0;
			virtual void SetPos(const Vector2f& delta) = 0;
	};
}
