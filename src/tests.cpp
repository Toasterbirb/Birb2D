#ifndef DOCTEST_CONFIG_DISABLE
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#endif

#include "doctest.h"
#include "Entity.hpp"
#include "Utils.hpp"
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
	SDL_Texture* texture = Birb2D::Render::LoadTexture("/home/toasterbirb/git/birb2d/res/textures/giga_stretch.png");

	CHECK(window.win_title == "Title");
	CHECK(window.window_dimensions.x == 1280);
	CHECK(window.window_dimensions.y == 720);
	CHECK(window.refresh_rate == 60);
	CHECK(window.win != NULL);
	CHECK(window.renderer != NULL);
	CHECK(texture != nullptr);

	CHECK_NOTHROW(window.Clear());
	CHECK_NOTHROW(window.Display());
	CHECK_NOTHROW(window.Cleanup());
}
