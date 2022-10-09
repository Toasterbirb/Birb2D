#include "Scene.hpp"
#include "Renderwindow.hpp"

namespace Birb
{
	Scene::Scene()
	:active(true), positionOffset(0, 0)
	{}

	Scene::Scene(const bool& isActive)
	:active(isActive), positionOffset(0, 0)
	{}

	void Scene::AddObject(SceneObject* obj)
	{
		objects.push_back(obj);

		/* If the positionOffset has changed, apply that to new objects */
		if (positionOffset != Vector2(0, 0))
			obj->SetPos(positionOffset);

		/* If the object has non-zero rendering priority, enable scene sorting */
		if (obj->renderingPriority != 0)
			needs_sorting = true;

		if (needs_sorting)
			SortObjects();
	}

	void Scene::AddObjectFast(SceneObject* obj)
	{
		objects.push_back(obj);

		/* If the positionOffset has changed, apply that to new objects */
		if (positionOffset != Vector2(0, 0))
			obj->SetPos(positionOffset);
	}

	void Scene::AddObject(SceneObject* obj[], int objCount)
	{
		for (int i = 0; i < objCount; ++i)
			obj[i]->SetPos(positionOffset);

		this->objects.insert(std::end(this->objects), obj, obj + objCount);
		SortObjects();
	}

	void Scene::PreAllocate(const int& objCount)
	{
		objects.reserve(objCount);
	}

	std::vector<SceneObject*> Scene::GetObjects() const
	{
		return objects;
	}

	int Scene::ObjectCount() const
	{
		return objects.size();
	}

	void Scene::Activate()
	{
		active = true;

		/* Mark the scene as active in scene objects */
		for (size_t i = 0; i < objects.size(); ++i)
			objects[i]->sceneActive = true;
	}

	void Scene::Deactivate()
	{
		active = false;

		/* Mark the scene as inactive in scene objects */
		for (size_t i = 0; i < objects.size(); ++i)
			objects[i]->sceneActive = false;
	}

	void Scene::Toggle()
	{
		active = !active;

		/* Toggle the scene statuc in scene objects */
		for (size_t i = 0; i < objects.size(); ++i)
			objects[i]->sceneActive = active;
	}

	bool Scene::isActive() const
	{
		return active;
	}

	void Scene::SetPosition(const Vector2& newPosition)
	{
		/* Calculate the delta between the current and new position */
		Vector2 delta = newPosition - positionOffset;
		positionOffset = positionOffset + delta;

		/* Set new positions for all of the scene objects */
		for (size_t i = 0; i < objects.size(); ++i)
		{
			objects[i]->SetPos(delta);
		}
	}

	void Scene::Translate(const Vector2& delta)
	{
		positionOffset = positionOffset + delta;

		/* Set new positions for all of the scene objects */
		for (size_t i = 0; i < objects.size(); ++i)
		{
			objects[i]->SetPos(delta);
		}
	}

	Vector2 Scene::Position() const
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
		for (size_t i = 0; i < objects.size(); ++i)
			if (objects[i]->active)
				objects[i]->RenderFunc();
	}

	void Scene::SortObjects()
	{
		SceneObject* tmpObject;
		int j;

		for (size_t i = 1; i < objects.size(); ++i)
		{
			tmpObject = objects[i];
			j = i - 1;

			while (j >= 0 && objects[j]->renderingPriority > tmpObject->renderingPriority)
			{
				objects[j + 1] = objects[j];
				j = j - 1;
			}
			objects[j + 1] = tmpObject;
		}
	}

	void Scene::RenderFunc()
	{
		this->Render();
	}

	void Scene::SetPos(const Vector2& delta)
	{
		this->Translate(delta);
	}
}
