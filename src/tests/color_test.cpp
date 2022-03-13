#include "doctest.h"
#include "Color.hpp"

namespace Birb
{
	TEST_CASE("Default color")
	{
		Color color;
		CHECK(color.r == 0);
		CHECK(color.g == 0);
		CHECK(color.b == 0);
		CHECK(color.a == 255);
	}

	TEST_CASE("Color with arguments")
	{
		Color colorA(10, 10, 20);
		Color colorB(10, 10, 20, 40);

		CHECK(colorA.r == 10);
		CHECK(colorA.g == 10);
		CHECK(colorA.b == 20);
		CHECK(colorA.a == 255);

		CHECK(colorB.r == 10);
		CHECK(colorB.g == 10);
		CHECK(colorB.b == 20);
		CHECK(colorB.a == 40);
	}

	TEST_CASE("Color to SDL_Color")
	{
		Color color(20, 45, 52, 10);
		SDL_Color sdlcolor = color.sdl();

		CHECK(sdlcolor.r == 20);
		CHECK(sdlcolor.g == 45);
		CHECK(sdlcolor.b == 52);
		CHECK(sdlcolor.a == 10);
	}

	TEST_CASE("Color comparison")
	{
		Color colorA(10, 32, 42, 12);
		Color colorB(10, 32, 42, 12);

		CHECK(colorA == colorB);
	}
}
