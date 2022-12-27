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

	TEST_CASE("Color with Vectors")
	{
		Color colorA(Vector3Int(10, 10, 20));
		Color colorB(Vector3(0.5f, 0.4f, 0.3f));

		CHECK(colorA.r == 10);
		CHECK(colorA.g == 10);
		CHECK(colorA.b == 20);
		CHECK(colorA.a == 255);

		CHECK(colorB.r == 128);
		CHECK(colorB.g == 102);
		CHECK(colorB.b == 77);
		CHECK(colorB.a == 255);
	}

	TEST_CASE("Color from SDL_Color")
	{
		SDL_Color sdl_color;
		sdl_color.r = 25;
		sdl_color.g = 64;
		sdl_color.b = 128;
		sdl_color.a = 9;

		Color color(sdl_color);
		CHECK(color.r == 25);
		CHECK(color.g == 64);
		CHECK(color.b == 128);
		CHECK(color.a == 9);
	}

	TEST_CASE("Color from hex")
	{
		Color colorA(0xFFFFFF);
		CHECK(colorA.r == 255);
		CHECK(colorA.g == 255);
		CHECK(colorA.b == 255);
		CHECK(colorA.a == 255);

		Color colorB(0x254E07);
		CHECK(colorB.r == 37);
		CHECK(colorB.g == 78);
		CHECK(colorB.b == 7);
		CHECK(colorB.a == 255);

		Color colorC(0x000000);
		CHECK(colorC.r == 0);
		CHECK(colorC.g == 0);
		CHECK(colorC.b == 0);
		CHECK(colorC.a == 255);

		Color colorD(0x00000000);
		CHECK(colorC.r == 0);
		CHECK(colorC.g == 0);
		CHECK(colorC.b == 0);
		CHECK(colorC.a == 255);
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

	TEST_CASE("Color operator overloads")
	{
		Color colorA(10, 32, 42, 12);
		Color colorB(10, 32, 42, 12);

		SUBCASE("Boolean comparison")
		{
			CHECK(colorA == colorB);
		}

		SUBCASE("Set color values to other color")
		{
			colorA = colorB;
			CHECK(colorA == colorB);
		}
	}

	TEST_CASE("Color intensity modification (lighten/darken)")
	{
		Color colorA(0xFFFFFF);
		CHECK(colorA.r == 255);
		CHECK(colorA.g == 255);
		CHECK(colorA.b == 255);
		CHECK(colorA.a == 255);

		colorA.ChangeIntensity(10);
		CHECK(colorA.r == 255);
		CHECK(colorA.g == 255);
		CHECK(colorA.b == 255);
		CHECK(colorA.a == 255);

		colorA.ChangeIntensity(-10);
		CHECK(colorA.r == 245);
		CHECK(colorA.g == 245);
		CHECK(colorA.b == 245);
		CHECK(colorA.a == 255);

		colorA.ChangeIntensity(-255);
		CHECK(colorA.r == 0);
		CHECK(colorA.g == 0);
		CHECK(colorA.b == 0);
		CHECK(colorA.a == 255);
	}
}
