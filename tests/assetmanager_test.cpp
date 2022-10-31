#include "doctest.h"
#include "AssetManager.hpp"
#include "Renderwindow.hpp"

namespace Birb
{
	TEST_CASE("Rendering: AssetManager texture resource handling")
	{
		Window window("Texture window", Vector2Int(1280, 720), 60, false);
		Texture birb_texture("./res/textures/birb.png");

		AssetManager asset_manager;
		asset_manager.LoadTexture("birb", "./res/textures/birb.png");
		CHECK(asset_manager.texture("birb").isLoaded());
		CHECK(asset_manager.texture("birb").dimensions() == Vector2Int(64, 64));
	}
}
