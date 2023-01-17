#include "doctest.h"

#include "ErrorFuse.hpp"
#include "Entities/Text.hpp"

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Error fuse")
	{
		ErrorFuse fuse;
		CHECK_FALSE(fuse.ErrorFuseStatus());

		fuse.BlowErrorFuse();
		CHECK(fuse.ErrorFuseStatus());
	}

	TEST_CASE("Error fuse in an entity")
	{
		/* A general fuse test with objects that use inheritance.
		 * This same should apply to all classes that inherit the
		 * ErrorFuse class*/

		Entity::Text text;
		CHECK_FALSE(text.ErrorFuseStatus());

		text.BlowErrorFuse();
		CHECK(text.ErrorFuseStatus());
	}
}
