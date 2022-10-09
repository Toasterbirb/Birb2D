#pragma once
#include "Color.hpp"
#include "Texture.hpp"
#include "Vector.hpp"
#include "Rect.hpp"
#include "Scene.hpp"
#include "STD.hpp"

namespace Birb
{
	class Level
	{
	public:
		Level(const Vector2Int& dimensions);
		Level(const std::string& level_path);

		Scene ToScene();
		void SetScale(float scale);
		void Save(const std::string file_path);

		struct Tile
		{
			Tile()
			{
				is_empty 	= true;
				is_collider = false;
				rect.color	= 0x000050;
			}

			bool is_empty;
			bool is_collider;
			Rect rect;
		};

		void SetTile(Vector2Int tile_pos, Tile tile);
		Tile GetTile(Vector2Int tile_pos) const;

	private:
		void PreallocateTiles(const Vector2Int& dimensions);

		Vector2Int grid_size;
		float scale;
		bool has_been_modified;
		Scene latest_scene;

		std::string file_path;
		std::vector<std::vector<Tile>> tiles;
	};
}
