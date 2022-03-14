#include "doctest.h"
#include "Scene.hpp"

namespace Birb
{
	TEST_CASE("Scenes")
	{
		Scene scene;

		Entity entityA("Test entity A");
		Entity entityB("Test entity B");
		entityB.renderingPriority = 5;

		Widgets::Graph graphs[2] = {
			Widgets::Graph(),
			Widgets::Graph(),
		};
		graphs[1].renderingPriority = 3;

		scene.AddObject(&entityA);
		scene.AddObject(&entityB);
		scene.AddObject(&graphs[0]);
		scene.AddObject(&graphs[1]);

		CHECK(scene.ObjectCount() == 4);
		
		std::vector<SceneObject*> objPointers = scene.GetObjects();
		CHECK(objPointers[objPointers.size() - 1] == &entityB);
		CHECK(objPointers[objPointers.size() - 2] == &graphs[1]);

		SUBCASE("Scene state changing")
		{
			scene.Deactivate();
			CHECK_FALSE(scene.isActive());

			scene.Activate();
			CHECK(scene.isActive());

			scene.Toggle();
			CHECK_FALSE(scene.isActive());
		}
	}
}
