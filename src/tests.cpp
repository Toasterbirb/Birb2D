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
	CHECK_NOTHROW(Debug::Log("Log (this is only a test)"));
	CHECK_NOTHROW(Debug::Log("Log (this is only a test)", Debug::log));
	CHECK_NOTHROW(Debug::Log("Warning (this is only a test)", Debug::warning));
	CHECK_NOTHROW(Debug::Log("Error (this is only a test)", Debug::error));
}

TEST_CASE("window and rendering functions")
{
	Birb2D::Window window("Title", Vector2int(1280, 720), 60);
	SDL_Texture* texture 	= Birb2D::Resources::LoadTexture("/home/toasterbirb/git/birb2d/res/textures/giga_stretch.png");
	TTF_Font* font 			= Birb2D::Resources::LoadFont("/home/toasterbirb/git/birb2d/res/fonts/freefont/FreeMonoBold.ttf", 32);

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
    Vector2f vector;
    CHECK(vector.x == 0);
    CHECK(vector.y == 0);
}

TEST_CASE("Vector2f with arguments")
{
    CHECK(Vector2f(1, 4).x == 1);
    CHECK(Vector2f(1, 4).y == 4);
    CHECK(Vector2f(1.53f, 5.21f).x == 1.53f);
    CHECK(Vector2f(1.53f, 5.21f).y == 5.21f);
}

TEST_CASE("Default Vector2int")
{
    Vector2int vector;
    CHECK(vector.x == 0);
    CHECK(vector.y == 0);
}

TEST_CASE("Vector2int with arguments")
{
    CHECK(Vector2int(1, 4).x == 1);
    CHECK(Vector2int(1, 4).y == 4);
    CHECK(Vector2int(1.53f, 5.21f).x == 2);
    CHECK(Vector2int(1.53f, 5.21f).y == 5);
}

TEST_CASE("Default Vector3f")
{
    Vector3f vector;
    CHECK(vector.x == 0);
    CHECK(vector.y == 0);
    CHECK(vector.z == 0);
}

TEST_CASE("Vector3f with arguments")
{
    CHECK(Vector3f(1, 4, 2).x == 1);
    CHECK(Vector3f(1, 4, 2).y == 4);
    CHECK(Vector3f(1, 4, 2).z == 2);
    CHECK(Vector3f(1.53f, 5.21f, 2.45f).x == 1.53f);
    CHECK(Vector3f(1.53f, 5.21f, 2.45f).y == 5.21f);
    CHECK(Vector3f(1.53f, 5.21f, 2.45f).z == 2.45f);
}

TEST_CASE("Default Vector3int")
{
    Vector3int vector;
    CHECK(vector.x == 0);
    CHECK(vector.y == 0);
    CHECK(vector.z == 0);
}

TEST_CASE("Vector3int with arguments")
{
    CHECK(Vector3int(1, 4, 2).x == 1);
    CHECK(Vector3int(1, 4, 2).y == 4);
    CHECK(Vector3int(1, 4, 2).z == 2);
    CHECK(Vector3int(1.53f, 5.21f, 2.45f).x == 2);
    CHECK(Vector3int(1.53f, 5.21f, 2.45f).y == 5);
    CHECK(Vector3int(1.53f, 5.21f, 2.45f).z == 2);
}

TEST_CASE("Default Rect")
{
    Rect defaultRect;
    CHECK(defaultRect.x == 0);
    CHECK(defaultRect.y == 0);
    CHECK(defaultRect.w == 0);
    CHECK(defaultRect.h == 0);

}

TEST_CASE("Rect with arguments")
{
    Rect customRect(10.54, 20, 30.234, 40.6668);
    CHECK(customRect.x == 10.54f);
    CHECK(customRect.y == 20);
    CHECK(customRect.w == 30.234f);
    CHECK(customRect.h == 40.6668f);
}

TEST_CASE("Rect with rounded values (integer)")
{
    Rect customRect(10.54, 20, 30.234, 40.6668);
    Rect roundedRect = customRect.getInt();

    CHECK(roundedRect.x == 11);
    CHECK(roundedRect.y == 20);
    CHECK(roundedRect.w == 30);
    CHECK(roundedRect.h == 41);
}
