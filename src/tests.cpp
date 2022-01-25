#ifndef DOCTEST_CONFIG_DISABLE
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#endif

#include "doctest.h"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Math.hpp"
#include "Audio.hpp"
#include "Values.hpp"
#include "Logger.hpp"
#include "Renderwindow.hpp"


TEST_CASE("logging")
{
	CHECK_NOTHROW(Birb::Debug::Log("Log (this is only a test)"));
	CHECK_NOTHROW(Birb::Debug::Log("Log (this is only a test)", Birb::Debug::log));
	CHECK_NOTHROW(Birb::Debug::Log("Warning (this is only a test)", Birb::Debug::warning));
	CHECK_NOTHROW(Birb::Debug::Log("Error (this is only a test)", Birb::Debug::error));
}

TEST_CASE("window and rendering functions")
{
	Birb::Window window("Title", Birb::Vector2int(1280, 720), 60, false);
	SDL_Texture* texture 	= Birb::Resources::LoadTexture("/home/toasterbirb/git/birb2d/res/textures/giga_stretch.png");
	TTF_Font* font 			= Birb::Resources::LoadFont("/home/toasterbirb/git/birb2d/res/fonts/freefont/FreeMonoBold.ttf", 32);

	CHECK(window.win_title == "Title");
	CHECK(window.window_dimensions.x == 1280);
	CHECK(window.window_dimensions.y == 720);
	CHECK(window.refresh_rate == 60);
	CHECK(window.win 		!= NULL);
	CHECK(window.renderer 	!= NULL);
	CHECK(texture 	!= nullptr);
	CHECK(font 		!= nullptr);

	CHECK_NOTHROW(window.Clear());
	CHECK_NOTHROW(window.Display());
	CHECK_NOTHROW(window.Cleanup());

	SDL_Quit();
}

// ### Math stuff and other utilities ###
TEST_CASE("Default Vector2f")
{
    Birb::Vector2f vector;
    CHECK(vector.x == 0);
    CHECK(vector.y == 0);
}

TEST_CASE("Vector2f with arguments")
{
    CHECK(Birb::Vector2f(1, 4).x == 1);
    CHECK(Birb::Vector2f(1, 4).y == 4);
    CHECK(Birb::Vector2f(1.53f, 5.21f).x == 1.53f);
    CHECK(Birb::Vector2f(1.53f, 5.21f).y == 5.21f);
}

TEST_CASE("Default Vector2int")
{
    Birb::Vector2int vector;
    CHECK(vector.x == 0);
    CHECK(vector.y == 0);
}

TEST_CASE("Vector2int with arguments")
{
    CHECK(Birb::Vector2int(1, 4).x == 1);
    CHECK(Birb::Vector2int(1, 4).y == 4);
    CHECK(Birb::Vector2int(1.53f, 5.21f).x == 2);
    CHECK(Birb::Vector2int(1.53f, 5.21f).y == 5);
}

TEST_CASE("Default Vector3f")
{
	Birb::Vector3f vector;
    CHECK(vector.x == 0);
    CHECK(vector.y == 0);
    CHECK(vector.z == 0);
}

TEST_CASE("Vector3f with arguments")
{
    CHECK(Birb::Vector3f(1, 4, 2).x == 1);
    CHECK(Birb::Vector3f(1, 4, 2).y == 4);
    CHECK(Birb::Vector3f(1, 4, 2).z == 2);
    CHECK(Birb::Vector3f(1.53f, 5.21f, 2.45f).x == 1.53f);
    CHECK(Birb::Vector3f(1.53f, 5.21f, 2.45f).y == 5.21f);
    CHECK(Birb::Vector3f(1.53f, 5.21f, 2.45f).z == 2.45f);
}

TEST_CASE("Default Vector3int")
{
	Birb::Vector3int vector;
    CHECK(vector.x == 0);
    CHECK(vector.y == 0);
    CHECK(vector.z == 0);
}

TEST_CASE("Vector3int with arguments")
{
    CHECK(Birb::Vector3int(1, 4, 2).x == 1);
    CHECK(Birb::Vector3int(1, 4, 2).y == 4);
    CHECK(Birb::Vector3int(1, 4, 2).z == 2);
    CHECK(Birb::Vector3int(1.53f, 5.21f, 2.45f).x == 2);
    CHECK(Birb::Vector3int(1.53f, 5.21f, 2.45f).y == 5);
    CHECK(Birb::Vector3int(1.53f, 5.21f, 2.45f).z == 2);
}

TEST_CASE("Distance calculation with 2D vectors")
{
	Birb::Vector2f pointAf(1.0f, 1.0f);
	Birb::Vector2f pointBf(8.0f, 3.0f);

	Birb::Vector2int pointAint(1, 1);
	Birb::Vector2int pointBint(8, 3);

	CHECK(Birb::Math::VectorDistance(pointAf, pointBf) == 7.2801098892805f);
	CHECK(Birb::Math::VectorDistance(pointAint, pointBint) == 7.2801098892805f);
}

TEST_CASE("Distance calculation with 3D vectors")
{
	Birb::Vector3f pointAf(1.0f, 1.0f, 1.0f);
	Birb::Vector3f pointBf(8.0f, 3.0f, 2.0f);

	Birb::Vector3int pointAint(1, 1, 1);
	Birb::Vector3int pointBint(8, 3, 2);

	CHECK(std::roundf(Birb::Math::VectorDistance(pointAf, pointBf)) == std::roundf(7.3484792283495));
	CHECK(std::roundf(Birb::Math::VectorDistance(pointAint, pointBint)) == std::roundf(7.3484692283495));
}

TEST_CASE("Calculate the centerpoint between two 2D vectors")
{
	Birb::Vector2f pointAf(1.0f, 1.0f);
	Birb::Vector2f pointBf(8.0f, 3.0f);

	Birb::Vector2int pointAint(1, 1);
	Birb::Vector2int pointBint(8, 3);

	Birb::Vector2f resultf = Birb::Math::CenterPoint(pointAf, pointBf);
	Birb::Vector2f resultint = Birb::Math::CenterPoint(pointAint, pointBint);
	Birb::Vector2f expectedResult(4.5f, 2.0f);

	CHECK(resultf == expectedResult);
	CHECK(resultint == expectedResult);
}

TEST_CASE("Calculate the centerpoint between two 3D vectors")
{
	Birb::Vector3f pointAf(1.0f, 1.0f, 1.0f);
	Birb::Vector3f pointBf(8.0f, 3.0f, 2.0f);

	Birb::Vector3int pointAint(1, 1, 1);
	Birb::Vector3int pointBint(8, 3, 2);

	Birb::Vector3f resultf = Birb::Math::CenterPoint(pointAf, pointBf);
	Birb::Vector3f resultint = Birb::Math::CenterPoint(pointAint, pointBint);
	Birb::Vector3f expectedResult(4.5f, 2.0f, 1.5f);

	CHECK(resultf == expectedResult);
	CHECK(resultint == expectedResult);
}

TEST_CASE("Vector2f operator overloads")
{
	Birb::Vector2f vecA(1.0f, 1.5f);
	Birb::Vector2f vecB(2.0f, 3.2f);

	CHECK(vecA + vecB == Birb::Vector2f(3.0f, 4.7f));
	CHECK(vecA - vecB == Birb::Vector2f(-1.0f, -1.7f));
	CHECK(vecA * vecB == Birb::Vector2f(2.0f, 4.8f));
	CHECK(vecA / vecB == Birb::Vector2f(0.5f, 0.46875f));
}

TEST_CASE("Vector2int operator overloads")
{
	Birb::Vector2int vecA(4, 2);
	Birb::Vector2int vecB(2, 3);

	CHECK(vecA + vecB == Birb::Vector2int(6, 5));
	CHECK(vecA - vecB == Birb::Vector2int(2, -1));
	CHECK(vecA * vecB == Birb::Vector2int(8, 6));
	CHECK(vecA / vecB == Birb::Vector2int(2, 1));
}

TEST_CASE("Vector3f operator overloads")
{
	Birb::Vector3f vecA(1.0f, 1.5f, 0.2f);
	Birb::Vector3f vecB(2.0f, 3.2f, 2.0f);

	CHECK(vecA + vecB == Birb::Vector3f(3.0f, 4.7f, 2.2f));
	CHECK(vecA - vecB == Birb::Vector3f(-1.0f, -1.7f, -1.8f));
	CHECK(vecA * vecB == Birb::Vector3f(2.0f, 4.8f, 0.4f));
	CHECK(vecA / vecB == Birb::Vector3f(0.5f, 0.468750f, 0.1f));
}

TEST_CASE("Vector3int operator overloads")
{
	Birb::Vector3int vecA(4, 6, 5);
	Birb::Vector3int vecB(2, 3, 2);

	CHECK(vecA + vecB == Birb::Vector3int(6, 9, 7));
	CHECK(vecA - vecB == Birb::Vector3int(2, 3, 3));
	CHECK(vecA * vecB == Birb::Vector3int(8, 18, 10));
	CHECK(vecA / vecB == Birb::Vector3int(2, 2, 3));
}

TEST_CASE("Default Rect")
{
	Birb::Rect defaultRect;
    CHECK(defaultRect.x == 0);
    CHECK(defaultRect.y == 0);
    CHECK(defaultRect.w == 0);
    CHECK(defaultRect.h == 0);

}

TEST_CASE("Rect with arguments")
{
	Birb::Rect customRect(10.54, 20, 30.234, 40.6668);
    CHECK(customRect.x == 10.54f);
    CHECK(customRect.y == 20);
    CHECK(customRect.w == 30.234f);
    CHECK(customRect.h == 40.6668f);
}

TEST_CASE("Rect with rounded values (integer)")
{
	Birb::Rect customRect(10.54, 20, 30.234, 40.6668);
    Birb::Rect roundedRect = customRect.getInt();

    CHECK(roundedRect.x == 11);
    CHECK(roundedRect.y == 20);
    CHECK(roundedRect.w == 30);
    CHECK(roundedRect.h == 41);
}
