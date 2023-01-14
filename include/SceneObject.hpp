#pragma once

namespace Birb
{
	struct Vector2;

	class SceneObject
	{
	public:
		constexpr SceneObject()
		:renderingPriority(0), sceneActive(true), active(true), world_space(true), parallax_multiplier(1) {}

		SceneObject(const int& priority)
		:renderingPriority(priority), sceneActive(true), active(true), world_space(true), parallax_multiplier(1) {}

		constexpr SceneObject(const int& priority, const bool& active)
		:renderingPriority(priority), sceneActive(true), active(active), world_space(true), parallax_multiplier(1) {}

		//virtual ~SceneObject() 						= default;
		constexpr SceneObject(const SceneObject&) 	= default;
		constexpr SceneObject(SceneObject&&) 		= default;
		SceneObject& operator=(const SceneObject&) 	= default;
		SceneObject& operator=(SceneObject&&) 		= default;

		/// The rendering priority determnies the order that objects are rendered with
		short renderingPriority;

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
