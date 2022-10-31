#include "AssetManager.hpp"

namespace Birb
{
	AssetManager::AssetManager()
	{}

	void AssetManager::AddTexture(const std::string& name, Texture texture)
	{
		textures[name] = texture;
	}

	void AssetManager::LoadTexture(const std::string& name, const std::string& file_path)
	{
		Texture texture(file_path);
		textures[name] = texture;
	}

	Texture& AssetManager::texture(const std::string& name)
	{
		return textures[name];
	}
}
