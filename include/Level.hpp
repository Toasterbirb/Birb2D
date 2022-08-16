#pragma once
#include "Color.hpp"
#include "Texture.hpp"
#include "Vector.hpp"
#include "STD.hpp"

namespace Birb
{
	class Level
	{
	public:
		Level(const Vector2int& dimensions);
		Level(const std::string& level_path);
		void Save(const std::string file_path);

		struct Tile
		{
			bool is_collider;
			Birb::Color color;
			Birb::Texture* sprite;
		};

	private:
		void PreallocateTiles(const Vector2int& dimensions);

		Vector2int grid_size;
		std::string file_path;
		std::vector<std::vector<Tile>> tiles;
	};
}
