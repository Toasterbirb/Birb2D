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
	Birb::Window window("Title", Birb::Vector2int(1280, 720), 60);
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
