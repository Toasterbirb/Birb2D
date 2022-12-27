#include "doctest.h"
#include "Renderwindow.hpp"
#include "Texture.hpp"

const static Birb::Vector2Int birb_texture_dimensions = Birb::Vector2Int(64, 64);

namespace Birb
{
	TEST_CASE("Rendering: Texture construction")
	{
		Window window("Texture window", Vector2Int(1280, 720), 60, false);

		SUBCASE("Empty texture constructor")
		{
			Texture texture;
			CHECK(texture.dimensions() == Vector2Int(0, 0));
			CHECK(texture.isLoaded() == false);
		}

		SUBCASE("Texture constuction with a filepath")
		{
			Texture texture("textures/birb.png");
			CHECK(texture.dimensions() == birb_texture_dimensions);
			CHECK(texture.isLoaded());
		}

		SUBCASE("Texture construction after creating an empty texture")
		{
			Texture texture;
			texture.LoadTexture("textures/birb.png");
			CHECK(texture.dimensions() == birb_texture_dimensions);
			CHECK(texture.isLoaded());
		}
	}
}
