#include "Level.hpp"

namespace Birb
{
	Level::Level(const Vector2int& dimensions)
	:grid_size(dimensions)
	{
		/* Creates a new level */

		/* Preallocate tiles */
		PreallocateTiles(dimensions);
	}

	Level::Level(const std::string& level_path)
	:file_path(level_path)
	{
		// TODO: Read the grid size from the file
		// Lets set it to 64x64 by default for now
		grid_size = Vector2int(64, 64);
	}

	void Level::PreallocateTiles(const Vector2int& dimensions)
	{
		tiles.reserve(dimensions.x);
		for (int i = 0; i < dimensions.x; i++)
		{
			tiles[i].reserve(dimensions.y);
		}
	}
}
