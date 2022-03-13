#pragma once

#include <vector>
#include "Entity.hpp"
#include "Graphs.hpp"
#include "Line.hpp"

namespace Birb
{
	class Scene
	{
	public:
		Scene();
		void AddObject(SceneObject* obj);
		
		int ObjectCount();

		void Activate();
		void Deactivate();
		void Toggle();
		bool isActive() const;

		void Render() const; ///< Render all objects in the scene if the scene is active

	private:
		void SetObjectState(bool state);

		std::vector<SceneObject*> objects;
		bool active;
	};
}
