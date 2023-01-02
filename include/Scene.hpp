#pragma once

#include "STD.hpp"
#include "Vector.hpp"
#include "SceneObject.hpp"

namespace Birb
{
	class Scene : public SceneObject
	{
	public:
		Scene();
		Scene(const bool& isActive);
		void AddScene(Scene* scene); ///< Same as AddObject() but has extra safety checks for adding scenes
		void AddObject(SceneObject* obj); ///< Add SceneObject to the scene and sort the scene
		void AddObjectFast(SceneObject* obj); ///< Add SceneObject to the scene, but skip sorting
		void AddObject(SceneObject** obj, int objCount); ///< Add multiple SceneObjects to the scene and sort the scene
		void PreAllocate(const int& objCount); ///< If you know approximately how many objects you are going to add
											   /// pre-allocating the memory can help reduce unnecessary std::vector
											   /// resizing
		std::vector<SceneObject*> GetObjects() const;

		int ObjectCount() const;

		/// Do a recursive check if the object is already in the scene.
		/// This can also be used to avoid circular scene dependencies
		bool SceneIsInScene(Scene* scene, Scene* calling_scene) const;

		void Activate();
		void Deactivate();
		void Toggle();
		bool isActive() const;

		void SetPosition(const Vector2& newPosition);
		void Translate(const Vector2& delta);
		Vector2 Position() const;

		void SetWorldSpace(); ///< Sets all current and future child objects to use world space coordinates
		void SetScreenSpace(); ///< Sets all current and future child objects to use screen space coordinates

		void Clear(); ///< Empty the scene
		void Render() const; ///< Render all objects in the scene if the scene is active
		void SortObjects(); ///< Sort objects according to their priority

	private:
		bool needs_sorting; ///< Set this to true if a SceneObject gets added with
							/// rendering priority != 0

		std::vector<SceneObject*> objects;

		/// Parent scene pointers are only stored if the
		/// AddScene() function is used. This is used for circular
		/// dependency prevention
		std::vector<Scene*> parent_scenes;

		bool active;

		Vector2 positionOffset;

		void SetNewObjectWorldSpace(SceneObject* obj); ///< Apply world_space settings of the scnene to new SceneObjects
		void PrintCircularDependendencyWarning() const;

		/* Variables for a scene that is a child of another scene */
		void RenderFunc() override; ///< Gets called when the scene is a child of another scene
		void SetPos(const Vector2& delta) override; ///< The same as Translate, used when the scene is a SceneObject
	};
}
