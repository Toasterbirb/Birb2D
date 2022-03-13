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
	}
}
