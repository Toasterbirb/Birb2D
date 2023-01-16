#include "doctest.h"
#include "Birb2D.hpp"

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Splash screen tests")
	{
		TTF_Init();

		SUBCASE("Rendering: Splash screen 4:3")
		{
			Window window("Birb2D tests", Vector2Int(1280, 960), 75, false);
			Splash splash_screen(window);
			splash_screen.Run();
			CHECK_FALSE(splash_screen.ErrorFuseStatus());
		}

		SUBCASE("Rendering: Splash screen 16:9")
		{
			Window window("Birb2D tests", Vector2Int(1280, 720), 75, false);
			Splash splash_screen(window);
			splash_screen.Run();
			CHECK_FALSE(splash_screen.ErrorFuseStatus());
		}

		SUBCASE("Rendering: Splash screen 21:9")
		{
			Window window("Birb2D tests", Vector2Int(1280, 549), 75, false);
			Splash splash_screen(window);
			splash_screen.Run();
			CHECK_FALSE(splash_screen.ErrorFuseStatus());
		}

		SUBCASE("Rendering: Custom splash screen 16:9")
		{
			Window window("Birb2D tests", Vector2Int(1280, 720), 75, false);
			Splash splash_screen(window, true);
			splash_screen.duration = 0.5;
			splash_screen.isCustom = true;

			/* Create a scene to show in the custom splash screen */
			Scene scene;
			Font font("birb2d_res/fonts/manaspace/manaspc.ttf", 24);
			Entity::Text splash_text("Custom splash screen test", &font, Colors::Nord::Aurora::nord15);
			splash_text.rect = Vector2Int(64, 64);
			scene.AddObject(&splash_text);
			splash_screen.scene = scene;

			splash_screen.Run();

			CHECK_FALSE(splash_text.ErrorFuseStatus());
			CHECK_FALSE(splash_screen.ErrorFuseStatus());
		}

		TTF_Quit();
	}
}
