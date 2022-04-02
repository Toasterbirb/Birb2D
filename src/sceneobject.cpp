#include "SceneObject.hpp"

namespace Birb
{
	SceneObject::SceneObject()
	{
		renderingPriority = 0;
		sceneActive = true;
		active = true;
	}

	SceneObject::SceneObject(const int& priority)
		:renderingPriority(priority)
	{
		active = true;
	}

	SceneObject::SceneObject(const int& priority, const bool& active)
		:renderingPriority(priority), active(active)
	{}
}
