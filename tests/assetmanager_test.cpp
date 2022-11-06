#include "doctest.h"
#include "AssetManager.hpp"
#include "Renderwindow.hpp"

namespace Birb
{
	TEST_CASE("Rendering: AssetManager texture resource handling")
	{
		Window window("Texture window", Vector2Int(1280, 720), 60, false);
		AssetManager::InitializeBundledAssets();
		Texture birb_texture("textures/birb.png");

		AssetManager asset_manager;

		/* Load a texture with the asset manager */
		asset_manager.LoadTexture("birb", "textures/birb.png");
		CHECK(asset_manager.texture("birb").isLoaded());
		CHECK(asset_manager.texture("birb").dimensions() == Vector2Int(64, 64));

		/* Copy an existing texture into the asset manager */
		asset_manager.AddTexture("existing_birb_texture", birb_texture);
		CHECK(asset_manager.texture("existing_birb_texture").isLoaded());
		CHECK(asset_manager.texture("existing_birb_texture").dimensions() == Vector2Int(64, 64));
		CHECK(asset_manager.texture("existing_birb_texture") == birb_texture);
	}

#ifdef BUNDLED_ASSETS
	TEST_CASE("Load an assets from an asset bundle")
	{
		CHECK(AssetManager::InitializeBundledAssets());
	}
#endif
}
