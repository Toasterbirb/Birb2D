#include "doctest.h"
#include "Birb2D.hpp"

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Construct an empty entity")
	{
		Entity::Empty empty;
		CHECK(empty.name == "Default Entity");
	}

	TEST_CASE("Empty entity with a name")
	{
		Entity::Empty empty("Entity");
		CHECK(empty.name == "Entity");
	}
}
