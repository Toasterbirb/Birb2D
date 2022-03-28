#pragma once

#include <vector>
#include "Vector.hpp"
#include "SceneObject.hpp"

namespace Birb
{
	class Scene
	{
	public:
		Scene();
		void AddObject(SceneObject* obj);
		void AddObject(SceneObject* obj[], int objCount);
		std::vector<SceneObject*> GetObjects() const;
		
		int ObjectCount();

		void Activate();
		void Deactivate();
		void Toggle();
		bool isActive() const;

		void SetPosition(const Vector2f& newPosition);
		void Translate(const Vector2f& delta);

		void Render() const; ///< Render all objects in the scene if the scene is active

	private:
		void SortObjects(); ///< Sort objects according to their priority

		std::vector<SceneObject*> objects;
		bool active;

		Vector2f positionOffset;
	};
}
