#include "doctest.h"
#include "AssetManager.hpp"
#include "Diagnostics.hpp"
#include "Renderwindow.hpp"
#include <vector>

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Rendering: AssetManager texture resource handling")
	{
		Window window("Texture window", Vector2Int(1280, 720), 60, false);
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

	TEST_CASE("Rendering: Lazy load textures")
	{
		Diagnostics::Debugging::AssetLoading = true;

		/* Window is needed, because loading a texture requires a renderer */
		Window window("Asset manager texture lazy loading", Vector2Int(1280, 720), 60, false);

		AssetManager asset_manager;
		asset_manager.LazyLoadQueue("birb2d_res/logo.png", TEXTURE);
		asset_manager.LazyLoadQueue("birb2d_res/loading.png", TEXTURE);
		asset_manager.LazyLoadQueue("textures/birb.png", TEXTURE);
		asset_manager.LazyLoadQueue("textures/birb_animation.png", TEXTURE);

		/* Start loading in the assets */
		asset_manager.LazyLoad();

		/* Do some error checking */
		CHECK_FALSE(asset_manager.ErrorFuseStatus());
		CHECK_FALSE(asset_manager.texture("birb2d_res/logo.png").ErrorFuseStatus());
		CHECK_FALSE(asset_manager.texture("birb2d_res/loading.png").ErrorFuseStatus());
		CHECK_FALSE(asset_manager.texture("textures/birb.png").ErrorFuseStatus());
		CHECK_FALSE(asset_manager.texture("textures/birb_animation.png").ErrorFuseStatus());

		CHECK(asset_manager.texture("birb2d_res/logo.png").dimensions() == Vector2Int(13, 11));

		Diagnostics::Debugging::AssetLoading = false;
	}
}
