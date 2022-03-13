#include "Scene.hpp"

namespace Birb
{
	void Scene::AddObject(Entity* entity)
	{
		entities.push_back(entity);
	}

	void Scene::AddObject(Widgets::Graph* graph)
	{
		graphs.push_back(graph);
	}

	bool Scene::HasObject(const Entity& entity) const
	{
		for (int i = 0; i < (int)entities.size(); i++)
		{
			if (*entities[i] == entity)
				return true;
		}

		return false;
	}

	bool Scene::HasObject(const Widgets::Graph& graph) const
	{
		for (int i = 0; i < (int)entities.size(); i++)
		{
			if (*graphs[i] == graph)
				return true;
		}

		return false;
	}

	int Scene::ObjectCount()
	{
		return entities.size() + graphs.size();
	}
}
