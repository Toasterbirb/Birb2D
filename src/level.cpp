#include "Filesystem.hpp"
#include "Level.hpp"
#include "Logger.hpp"

using namespace nlohmann;

/* json keys */
#define JSON_IS_EMPTY "e"
#define JSON_IS_COLLIDER "c"
#define JSON_COLOR_R "r"
#define JSON_COLOR_G "g"
#define JSON_COLOR_B "b"
#define JSON_COLOR_A "a"

namespace Birb
{
	Level::Tile::Tile(json json_object)
	{
		is_empty 		= json_object[JSON_IS_EMPTY];
		is_collider 	= json_object[JSON_IS_COLLIDER];
		rect.color.r 	= json_object[JSON_COLOR_R];
		rect.color.g 	= json_object[JSON_COLOR_G];
		rect.color.b 	= json_object[JSON_COLOR_B];
		rect.color.a 	= json_object[JSON_COLOR_A];
	}
	
	nlohmann::json Level::Tile::ToJson() const
	{
		json json_object;
		
		json_object[JSON_IS_EMPTY] 		= this->is_empty;
		json_object[JSON_IS_COLLIDER] 	= this->is_collider;
		json_object[JSON_COLOR_R] 		= this->rect.color.r;
		json_object[JSON_COLOR_G] 		= this->rect.color.g;
		json_object[JSON_COLOR_B] 		= this->rect.color.b;
		json_object[JSON_COLOR_A] 		= this->rect.color.a;

		return json_object;
	}

	Level::Level() {}

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
		has_been_modified = true;
		scale = 1.0f;

		std::string json_string = Birb::Filesystem::File::Read(level_path);
		json_data = json::parse(json_string);

		grid_size.x = json_data["level_size_x"];
		grid_size.y = json_data["level_size_y"];

		/* Allocate the grid */
		tiles = std::vector<std::vector<Tile>>(grid_size.x);
		for (int i = 0; i < grid_size.x; ++i)
			tiles[i] = std::vector<Tile>(grid_size.y);

		/* Read the grid from the json data */
		for (int i = 0; i < grid_size.x; ++i)
			for (int j = 0; j < grid_size.y; ++j)
				tiles[i][j] = Tile(json_data["tiles"][i][j]);
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

	void Level::Save(const std::string& file_path)
	{
		/* Update the json data */
		for (int i = 0; i < grid_size.x; ++i)
			for (int j = 0; j < grid_size.y; ++j)
				json_data["tiles"][i][j] = tiles[i][j].ToJson();

		std::ofstream file(file_path);
		file << std::setw(4) << json_data << std::endl;
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

	Vector2Int Level::GridSize() const
	{
		return grid_size;
	}


	void Level::CreateLevelFile(const Vector2Int& dimensions, char* file_path)
	{
		json new_level;
		new_level["level_size_x"] = dimensions.x;
		new_level["level_size_y"] = dimensions.y;

		json empty_tile = Tile().ToJson();

		for (int i = 0; i < dimensions.x; ++i)
			for (int j = 0; j < dimensions.y; ++j)
				new_level["tiles"][i][j] = empty_tile;

		/* Write the file */
		std::ofstream file(file_path);
		file << std::setw(4) << new_level << std::endl;
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
