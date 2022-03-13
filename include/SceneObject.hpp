#pragma once

namespace Birb
{
	class SceneObject
	{
	public:
		SceneObject();
		SceneObject(const int& priority);
		int renderingPriority;
		virtual void RenderFunc() = 0;
	};
}
