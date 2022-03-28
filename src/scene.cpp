#include "Scene.hpp"
#include "Renderwindow.hpp"

namespace Birb
{
	Scene::Scene()
	{
		active = true;
		positionOffset = {0, 0};
	}

	void Scene::AddObject(SceneObject* obj)
	{
		objects.push_back(obj);
		SortObjects();
	}

	void Scene::AddObject(SceneObject* obj[], int objCount)
	{
		this->objects.insert(std::end(this->objects), obj, obj + objCount);
	}

	std::vector<SceneObject*> Scene::GetObjects() const
	{
		return objects;
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

	void Scene::SetPosition(const Vector2f& newPosition)
	{
		/* Calculate the delta between the current and new position */
		Vector2f delta = newPosition - positionOffset;

		/* Set new positions for all of the scene objects */
		for (int i = 0; i < (int)objects.size(); i++)
		{
			objects[i]->SetPos(delta);
		}
	}

	void Scene::Translate(const Vector2f& delta)
	{
		/* Set new positions for all of the scene objects */
		for (int i = 0; i < (int)objects.size(); i++)
		{
			objects[i]->SetPos(delta);
		}
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

	/// FIXME: Switch bubble sort to some other more performant algorithm
	void Scene::SortObjects()
	{
		SceneObject* tmpObject;
		bool ready;
		do
		{
			ready = true;
			for (int i = 0; i < (int)objects.size() - 1; i++)
			{
				if (objects[i]->renderingPriority > objects[i + 1]->renderingPriority)
				{
					tmpObject = objects[i];
					objects[i] = objects[i + 1];
					objects[i + 1] = tmpObject;
					ready = false;
				}
			}
		} while (!ready);
	}
}
