#include "doctest.h"
#include "Rect.hpp"
#include "Var.hpp"

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Integer")
	{
		var value = 8;

		CHECK_FALSE(value.HasChanged());

		value = 9;
		CHECK(value.HasChanged());
		CHECK_FALSE(value.HasChanged());

		int integer = value.value();
		CHECK(integer == 9);
	}

	TEST_CASE("Boolean")
	{
		var boolean = false;
		CHECK_FALSE(boolean.HasChanged());

		boolean = true;
		CHECK(boolean.HasChanged());
		CHECK(boolean == true);
	}

	TEST_CASE("Rect")
	{
		var rect = Rect(0, 10, 256, 256);
		CHECK(rect.value().w == 256);

		rect.value().x = 10;
		CHECK(rect.HasChanged());
		CHECK(rect.value() == Rect(10, 10, 256, 256));
	}
}

