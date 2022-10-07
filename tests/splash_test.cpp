#include "doctest.h"
#include "Birb2D.hpp"

namespace Birb
{
	TEST_CASE("Rendering: Splash screen 4:3")
	{
		Window window("Birb2D tests", Vector2Int(1280, 960), 75, false);
		Splash splash_screen(window);
		splash_screen.insertLoadingScreenFrame = true;
		splash_screen.Run();
	}

	TEST_CASE("Rendering: Splash screen 16:9")
	{
		Window window("Birb2D tests", Vector2Int(1280, 720), 75, false);
		Splash splash_screen(window);
		splash_screen.insertLoadingScreenFrame = true;
		splash_screen.Run();
	}

	TEST_CASE("Rendering: Splash screen 21:9")
	{
		Window window("Birb2D tests", Vector2Int(1280, 549), 75, false);
		Splash splash_screen(window);
		splash_screen.insertLoadingScreenFrame = true;
		splash_screen.Run();
	}

	TEST_CASE("Rendering: Custom splash screen 16:9")
	{
		Window window("Birb2D tests", Vector2Int(1280, 720), 75, false);
		Splash splash_screen(window, true);
		splash_screen.duration = 0.5;
		splash_screen.isCustom = true;
		splash_screen.insertLoadingScreenFrame = true;
		splash_screen.Run();
	}
}
