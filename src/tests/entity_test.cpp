#include "doctest.h"
#include "Entity.hpp"

TEST_CASE("Entity comparison")
{
	Birb::Entity entityA("First entity");
	CHECK(entityA == entityA);

	Birb::Entity entityB("Second entity");
	CHECK_FALSE(entityA == entityB);
	entityB.name = "First entity";
	CHECK_FALSE(entityA == entityB);
}
