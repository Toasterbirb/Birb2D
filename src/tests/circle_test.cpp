#include "doctest.h"
#include "Circle.hpp"
#include "Math.hpp"

TEST_CASE("Circles")
{
	Birb::Circle circleA(0, {0, 4});
	Birb::Circle circleB(1.5);
	Birb::Circle circleC(-1.5);

	SUBCASE("Variable construction")
	{
		CHECK(circleA.radius == 0);
		CHECK(circleA.pos == Birb::Vector2int(0, 4));
		CHECK(circleA.color == 0xFFFFFF);

		CHECK(circleB.radius == 1.5f);
		CHECK(circleB.pos == Birb::Vector2int(0, 0));
		CHECK(circleB.color == 0xFFFFFF);
	}

	SUBCASE("Circumference")
	{
		CHECK(circleA.Circumference() == 0);
		CHECK(Birb::Math::Round(circleB.Circumference(), 2) == 9.42);
		CHECK(Birb::Math::Round(circleC.Circumference(), 2) == -9.42);
	}

	SUBCASE("Diameter")
	{
		CHECK(circleA.Diameter() == 0);
		CHECK(circleB.Diameter() == 3);
		CHECK(circleC.Diameter() == -3);
	}
}
