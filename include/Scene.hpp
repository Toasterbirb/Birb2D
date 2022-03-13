#pragma once

#include <vector>
#include "Entity.hpp"
#include "Graphs.hpp"

namespace Birb
{
	class Scene
	{
	public:
		Scene() {}
		void AddObject(Entity* entity);
		void AddObject(Widgets::Graph* graph);
		
		bool HasObject(const Entity& entity) const;
		bool HasObject(const Widgets::Graph& graph) const;

		int ObjectCount();

	private:
		std::vector<Entity*> entities;
		std::vector<Widgets::Graph*> graphs;
	};
}
