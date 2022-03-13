#include "Scene.hpp"
#include "Renderwindow.hpp"

namespace Birb
{
	Scene::Scene()
	{
		active = true;
	}

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

	void Scene::SetObjectState(bool state)
	{
		/* Set state for entitites */
		for (int i = 0; i < (int)entities.size(); i++)
		{
			entities[i]->active = state;
		}
		
		/* Set state for graphs */
		for (int i = 0; i < (int)graphs.size(); i++)
		{
			graphs[i]->active = state;
		}
	}

	void Scene::Activate()
	{
		active = true;
		SetObjectState(true);
	}

	void Scene::Deactivate()
	{
		active = false;
		SetObjectState(false);
	}

	void Scene::Toggle()
	{
		active = !active;
		SetObjectState(active);
	}

	void Scene::Render() const
	{
		/* Skip rendering if the scene isn't active */
		if (!active)
			return;

		/* Draw entities */
		for (int i = 0; i < (int)entities.size(); i++)
			Render::DrawEntity(*entities[i]);

		/* Draw graphs */
		for (int i = 0; i < (int)graphs.size(); i++)
			graphs[i]->Render();
	}
}
