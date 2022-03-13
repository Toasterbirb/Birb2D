#include "Scene.hpp"
#include "Renderwindow.hpp"

namespace Birb
{
	Scene::Scene()
	{
		active = true;
	}

	void Scene::AddObject(SceneObject* obj)
	{
		objects.push_back(obj);
	}

	int Scene::ObjectCount()
	{
		return objects.size();
	}

	void Scene::Activate()
	{
		active = true;
	}

	void Scene::Deactivate()
	{
		active = false;
	}

	void Scene::Toggle()
	{
		active = !active;
	}

	bool Scene::isActive() const
	{
		return active;
	}

	void Scene::Render() const
	{
		/* Skip rendering if the scene isn't active */
		if (!active)
			return;

		/* Draw objects */
		for (int i = 0; i < (int)objects.size(); i++)
			objects[i]->RenderFunc();
	}
}
