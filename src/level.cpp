#include "Level.hpp"
#include "Logger.hpp"

namespace Birb
{
	Level::Level(const Vector2Int& dimensions)
	:grid_size(dimensions)
	{
		/* Creates a new level */
		has_been_modified = false;

		/* Preallocate tiles */
		PreallocateTiles(dimensions);
	}

	Level::Level(const std::string& level_path)
	:file_path(level_path)
	{
		// TODO: Read the grid size from the file
		// Lets set it to 64x64 by default for now
		grid_size = Vector2Int(32, 32);

		has_been_modified = false;
		scale = 1.0f;
	}


	Scene Level::ToScene()
	{
		if (!has_been_modified)
			return latest_scene;

		Scene scene;

		/* Loop trough the tiles */
		for (int i = 0; i < grid_size.x; ++i)
		{
			for (int j = 0; j < grid_size.y; ++j)
			{
				/* Check if the tile has something */
				if (!tiles[i][j].is_empty)
				{
					/** Add colored rects **/

					/* Calculate the rect size + position */
					tiles[i][j].rect.x = i * scale;
					tiles[i][j].rect.y = j * scale;
					tiles[i][j].rect.w = scale + 1;
					tiles[i][j].rect.h = scale + 1;

					scene.AddObject(&tiles[i][j].rect);
				}
			}
		}

		latest_scene.Clear();
		latest_scene = scene;
		has_been_modified = false;

		return scene;
	}

	void Level::SetScale(float scale)
	{
		has_been_modified = true;
		this->scale = scale;
	}

	void Level::SetTile(Vector2Int tile_pos, Tile tile)
	{
		/* Do some boundary checking */
		if (tile_pos.x < 0 || tile_pos.y < 0)
			return;

		if (tile_pos.x > grid_size.x - 1 || tile_pos.y > grid_size.y - 1)
			return;

		/* Create a new tile */
		tiles[tile_pos.x][tile_pos.y] = tile;
		tiles[tile_pos.x][tile_pos.y].is_empty = false;

		has_been_modified = true;
	}

	Level::Tile Level::GetTile(Vector2Int tile_pos) const
	{
		/* Do some bounds checking */
		if (tile_pos.x < 0 || tile_pos.y < 0
				|| tile_pos.x > grid_size.x - 1
				|| tile_pos.y > grid_size.y - 1)
		{
			Debug::Log("Tried to get a tile that was out of bounds!", Debug::warning);
			return Tile();
		}

		return tiles[tile_pos.x][tile_pos.y];
	}

	void Level::PreallocateTiles(const Vector2Int& dimensions)
	{
		tiles.reserve(dimensions.x);
		for (int i = 0; i < grid_size.x; ++i)
		{
			std::vector<Tile> line;
			line.reserve(dimensions.y);
			line.resize(dimensions.y);
			tiles.push_back(line);
		}

		has_been_modified = true;
	}
}
