#include "doctest.h"
#include "Level.hpp"

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Setting tiles")
	{
		Vector2Int level_dimensions = { 10, 10 };
		Level level(level_dimensions);

		Level::Tile tileA;
		tileA.is_collider = true;
		level.SetTile({ 1, 1 }, tileA);

		CHECK(level.GetTile({ 1, 1 }).is_collider);
		CHECK_FALSE(level.GetTile({ 1, 1 }).is_empty);
		CHECK(level.GetTile({ 1, 1 }).rect.color == 0x000050);
	}
}
