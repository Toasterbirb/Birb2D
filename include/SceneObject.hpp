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

		/// The rendering priority determnies the order that objects are rendered with
		int renderingPriority;

		/// Tells if the parent scene is active or not
		bool sceneActive;

		/// Is the object "active". Could mean visibility etc.
		bool active;

		/// Object is positioned in world space
		bool world_space;

		/// The position of the object is multiplied to achieve a parallax effect
		float parallax_multiplier;

		virtual void RenderFunc() = 0;
		virtual void SetPos(const Vector2& delta) = 0;
	};
}
