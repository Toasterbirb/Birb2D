#include "Scene.hpp"
#include "Logger.hpp"
#include "Renderwindow.hpp"
#include "microprofile.h"
#include <cassert>

#define PROFILER_GROUP "Scenes"
#define PROFILER_COLOR MP_WHITE

namespace Birb
{
	Scene::Scene()
	:needs_sorting(false), active(true), positionOffset(0, 0)
	{}

	Scene::Scene(bool isActive)
	:needs_sorting(false), active(isActive), positionOffset(0, 0)
	{}

	void Scene::AddObject(SceneObject& obj)
	{
		this->AddObjectSafe(&obj);
	}

	void Scene::AddObject(SceneObject* obj)
	{
		assert(obj != NULL);
		this->AddObjectSafe(obj);
	}

	void Scene::AddObjectFast(SceneObject& obj)
	{
		AddObjectUnSafe(&obj);
	}

	void Scene::AddObjectFast(SceneObject* obj)
	{
		assert(obj != NULL);
		AddObjectUnSafe(obj);
	}

	void Scene::AddObject(SceneObject* obj[], int objCount)
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Add multiple SceneObjects", PROFILER_COLOR);

		assert(obj != NULL);
		assert(objCount > 0);

		for (int i = 0; i < objCount; ++i)
		{
			obj[i]->SetPos(positionOffset);
			SetNewObjectWorldSpace(obj[i]);
		}

		this->objects.insert(std::end(this->objects), obj, obj + objCount);
		SortObjects();
	}

	void Scene::PreAllocate(int objCount)
	{
		assert(objCount > 0);
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
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Activate the scene", PROFILER_COLOR);

		active = true;

		/* Mark the scene as active in scene objects */
		for (size_t i = 0; i < objects.size(); ++i)
			objects[i]->sceneActive = true;
	}

	void Scene::Deactivate()
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Deactivate the scene", PROFILER_COLOR);

		active = false;

		/* Mark the scene as inactive in scene objects */
		for (size_t i = 0; i < objects.size(); ++i)
			objects[i]->sceneActive = false;
	}

	void Scene::Toggle()
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Toggle the scene", PROFILER_COLOR);

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
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Set scene position (set)", PROFILER_COLOR);

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
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Set scene position (translate)", PROFILER_COLOR);

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

	void Scene::SetWorldSpace()
	{
		world_space = true;
		for (size_t i = 0; i < objects.size(); ++i)
		{
			objects[i]->world_space = this->world_space;

			/* Update parallax multipliers just in case */
			objects[i]->parallax_multiplier = this->parallax_multiplier;
		}
	}

	void Scene::SetScreenSpace()
	{
		world_space = false;
		for (size_t i = 0; i < objects.size(); ++i)
		{
			objects[i]->world_space = world_space;

			/* Update parallax multipliers just in case */
			objects[i]->parallax_multiplier = this->parallax_multiplier;
		}
	}

	void Scene::Clear()
	{
		objects.clear();
		positionOffset = {0, 0};
	}

	void Scene::Render() const
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Render", PROFILER_COLOR);

		/* Skip rendering if the scene isn't active */
		if (!active)
			return;

		/* Draw objects */
		for (size_t i = 0; i < objects.size(); ++i)
		{
			assert(objects[i] != NULL);
			if (objects[i]->active)
				objects[i]->RenderFunc();
		}
	}

	void Scene::SortObjects()
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Sort SceneObjects", PROFILER_COLOR);

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

	void Scene::AddObjectSafe(SceneObject* obj)
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Add SceneObject", PROFILER_COLOR);

		/* Make sure that the object being added isn't the scene itself */
		if (obj == this)
		{
			PrintCircularDependendencyWarning();
			return;
		}

		/* Add the object into the scene object list */
		objects.push_back(obj);

		/* If the positionOffset has changed, apply that to new objects */
		obj->SetPos(positionOffset);

		/* If the object has non-zero rendering priority, enable scene sorting */
		if (obj->renderingPriority != 0)
			needs_sorting = true;

		if (needs_sorting)
			SortObjects();

		/* Make sure that the world / screen space settings are correct */
		SetNewObjectWorldSpace(obj);
	}

	void Scene::AddObjectUnSafe(SceneObject* obj)
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Add SceneObject (fast)", PROFILER_COLOR);

		/* Adding the object into itself will cause problems */
		assert(obj != this);

		objects.push_back(obj);

		/* If the positionOffset has changed, apply that to new objects */
		obj->SetPos(positionOffset);

		/* Apply world_space settings */
		SetNewObjectWorldSpace(obj);
	}

	void Scene::SetNewObjectWorldSpace(SceneObject* obj)
	{
		assert(obj != NULL);
		obj->world_space 			= this->world_space;
		obj->parallax_multiplier 	= this->parallax_multiplier;
	}

	void Scene::PrintCircularDependendencyWarning() const
	{
		Debug::Log("There was an attempt to add a scene into itself! This was prevented to avoid a stack overflow", Debug::warning);
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
