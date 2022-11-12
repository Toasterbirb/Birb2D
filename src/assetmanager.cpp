#include "AssetManager.hpp"
#include "Logger.hpp"
#include "Filesystem.hpp"

#ifdef BUNDLED_ASSETS
#include "AssetBundle.hpp"
#include "cppcodec/base64_rfc4648.hpp"
#endif

namespace Birb
{
	void Asset::Free()
	{
		free(buffer);
	}

	AssetManager::AssetManager()
	{}

	bool AssetManager::InitializeBundledAssets()
	{
#ifdef BUNDLED_ASSETS
#ifndef HEADER_ASSET
		Debug::Log("Game was compiled with BUNDLED_ASSETS enabled, but the AssetBundle.hpp wasn't included", Debug::fixme);
		return false;
#endif /* HEADER_ASSET */
		std::vector<unsigned char> zip_file = cppcodec::base64_rfc4648::decode(res);
		zip_error_t* error_code = 0;
		zip_source_t* source = zip_source_buffer_create(static_cast<void*>(&zip_file[0]), zip_file.size(), 1, error_code);
		zip_t* res_zip = zip_open_from_source(source, 0, error_code);
		zip_source_keep(source);

		int num_entries = zip_get_num_entries(res_zip, 0);
		Debug::Log("Loaded " + std::to_string(num_entries) + " assets");

		struct zip_stat file_info;
		struct zip_file* z_file;

		for (int i = 0; i < zip_get_num_entries(res_zip, 0); ++i)
		{
			if (zip_stat_index(res_zip, i, 0, &file_info) == 0)
			{
				/* Skip directories */
				int namelen = strlen(file_info.name);
				if (file_info.name[namelen - 1] == '/')
					continue;

				z_file = zip_fopen_index(res_zip, i, 0);
				char* buffer = static_cast<char*>(calloc(file_info.size, sizeof(char)));
				zip_fread(z_file, buffer, file_info.size);

				Asset asset;
				asset.buffer = buffer;
				asset.size = file_info.size;

				assets[file_info.name] = asset;
				asset_list.push_back(file_info.name);
			}
		}

		return num_entries;
#else /* BUNDLED_ASSETS */
		return true;
#endif /* BUNDLED_ASSETS */
	}

#ifdef BUNDLED_ASSETS
	SDL_RWops* AssetManager::sdl_mem_read(const std::string& file_path)
	{
		return SDL_RWFromMem(AssetManager::assets[file_path].buffer, AssetManager::assets[file_path].size);
	}
#endif

	void AssetManager::FreeBundledAssets()
	{
#ifdef BUNDLED_ASSETS
		for (size_t i = 0; i < AssetManager::asset_list.size(); ++i)
		{
			AssetManager::assets[AssetManager::asset_list[i]].Free();
		}
#endif
	}

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
