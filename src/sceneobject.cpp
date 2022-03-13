#include "SceneObject.hpp"

namespace Birb
{
	SceneObject::SceneObject()
	{
		renderingPriority = 0;
	}

	SceneObject::SceneObject(const int& priority)
	:renderingPriority(priority)
	{}
}
