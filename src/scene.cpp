#include "Scene.hpp"
#include "Renderwindow.hpp"

namespace Birb
{
	Scene::Scene()
	{
		active = true;
		positionOffset = {0, 0};
	}

	Scene::Scene(const bool& isActive)
	:active(isActive)
	{
		positionOffset = {0, 0};
	}

	void Scene::AddObject(SceneObject* obj)
	{
		objects.push_back(obj);

		/* If the positionOffset has changed, apply that to new objects */
		if (positionOffset != Vector2f(0, 0))
			obj->SetPos(positionOffset);

		SortObjects();
	}

	void Scene::AddObject(SceneObject* obj[], int objCount)
	{
		for (int i = 0; i < objCount; i++)
			obj[i]->SetPos(positionOffset);

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

		/* Mark the scene as active in scene objects */
		for (int i = 0; i < (int)objects.size(); i++)
			objects[i]->sceneActive = true;
	}

	void Scene::Deactivate()
	{
		active = false;

		/* Mark the scene as inactive in scene objects */
		for (int i = 0; i < (int)objects.size(); i++)
			objects[i]->sceneActive = false;
	}

	void Scene::Toggle()
	{
		active = !active;

		/* Toggle the scene statuc in scene objects */
		for (int i = 0; i < (int)objects.size(); i++)
			objects[i]->sceneActive = active;
	}

	bool Scene::isActive() const
	{
		return active;
	}

	void Scene::SetPosition(const Vector2f& newPosition)
	{
		/* Calculate the delta between the current and new position */
		Vector2f delta = newPosition - positionOffset;
		positionOffset = positionOffset + delta;

		/* Set new positions for all of the scene objects */
		for (int i = 0; i < (int)objects.size(); i++)
		{
			objects[i]->SetPos(delta);
		}
	}

	void Scene::Translate(const Vector2f& delta)
	{
		positionOffset = positionOffset + delta;

		/* Set new positions for all of the scene objects */
		for (int i = 0; i < (int)objects.size(); i++)
		{
			objects[i]->SetPos(delta);
		}
	}

	Vector2f Scene::Position() const
	{
		return positionOffset;
	}

	void Scene::Clear()
	{
		objects.clear();
		positionOffset = {0, 0};
	}

	void Scene::Render() const
	{
		/* Skip rendering if the scene isn't active */
		if (!active)
			return;

		/* Draw objects */
		for (int i = 0; i < (int)objects.size(); i++)
			if (objects[i]->active)
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

	void Scene::RenderFunc()
	{
		this->Render();
	}

	void Scene::SetPos(const Vector2f& delta)
	{
		this->Translate(delta);
	}
}
