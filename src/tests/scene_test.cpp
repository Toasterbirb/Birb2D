#include "doctest.h"
#include "Scene.hpp"

namespace Birb
{
	TEST_CASE("Scenes")
	{
		Scene scene;

		Entity entityA("Test entity A");
		Entity entityB("Test entity B");

		Widgets::Graph graphs[2] = {
			Widgets::Graph(),
			Widgets::Graph(),
		};

		scene.AddObject(&entityA);
		scene.AddObject(&entityB);
		scene.AddObject(&graphs[0]);
		scene.AddObject(&graphs[1]);

		CHECK(scene.ObjectCount() == 4);
		CHECK(scene.HasObject(entityA));
		CHECK(scene.HasObject(graphs[0]));

		SUBCASE("Scene state changing")
		{
			scene.Deactivate();
			CHECK_FALSE(entityA.active);
			CHECK_FALSE(entityB.active);
			CHECK_FALSE(graphs[0].active);
			CHECK_FALSE(graphs[1].active);

			scene.Activate();
			CHECK(entityA.active);
			CHECK(entityB.active);
			CHECK(graphs[0].active);
			CHECK(graphs[1].active);

			scene.Toggle();
			CHECK_FALSE(entityA.active);
			CHECK_FALSE(entityB.active);
			CHECK_FALSE(graphs[0].active);
			CHECK_FALSE(graphs[1].active);
		}
	}
}
