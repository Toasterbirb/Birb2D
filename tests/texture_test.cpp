#include "doctest.h"
#include "Texture.hpp"

const static Birb::Vector2Int birb_texture_dimensions = Birb::Vector2Int(64, 64);

namespace Birb
{
	TEST_CASE("Empty texture constructor")
	{
		Texture texture;
		CHECK(texture.dimensions() == Vector2Int(0, 0));
		CHECK(texture.isLoaded() == false);
	}

	TEST_CASE("Texture constuction with a filepath")
	{
		Texture texture("./res/textures/birb.png");
		CHECK(texture.dimensions() == birb_texture_dimensions);
		CHECK(texture.isLoaded());
	}

	TEST_CASE("Texture construction after creating an empty texture")
	{
		Texture texture;
		texture.LoadTexture("./res/textures/birb.png");
		CHECK(texture.dimensions() == birb_texture_dimensions);
		CHECK(texture.isLoaded());
	}
}
