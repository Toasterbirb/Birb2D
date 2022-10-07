#include "doctest.h"
#include "Entity.hpp"

namespace Birb
{
	TEST_CASE("Entity comparison")
	{
		Entity entityA("First entity");
		CHECK(entityA == entityA);

		Entity entityB("Second entity");
		CHECK_FALSE(entityA == entityB);
		entityB.name = "First entity";
		CHECK_FALSE(entityA == entityB);
	}

	TEST_CASE("Empty entity")
	{
		Entity entity;
		CHECK(entity.name == "Default Entity");
	}

	TEST_CASE("Use an uninitialized font in a text component")
	{
		Font font;
		Entity entity("Text entity",
				Vector2Int(0, 0),
				EntityComponent::Text("Some text", &font, &Colors::White));
	}
}
