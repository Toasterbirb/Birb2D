#include "AssetManager.hpp"
#include "Diagnostics.hpp"
#include "Filesystem.hpp"
#include "Logger.hpp"
#include "Resources.hpp"
#include "Values.hpp"
#include <algorithm>

#ifdef DISTCC
#if BIRB_MT == 1
#include <execution>
#endif /* BIRB_MT */

#include <fstream>
#endif /* DISTCC */

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

	void AssetManager::LazyLoadQueue(const std::string &file_path, AssetType type)
	{
		lazyload_queue.push_back(std::make_pair(file_path, type));
	}

	void AssetManager::LazyLoad()
	{
#if BIRB_MT == 1
		std::for_each(std::execution::par, lazyload_queue.begin(), lazyload_queue.end(),
			[this](std::pair<std::string, AssetType> lazy_asset)
			{
				if (Diagnostics::Debugging::AssetLoading)
					Debug::Log("Loading: " + lazy_asset.first);

				std::ifstream file(Global::FilePaths::Resources + lazy_asset.first, std::ifstream::binary);
				if (file)
				{
					Asset asset;
					asset.type = lazy_asset.second;

					/* Get the file length */
					file.seekg(0, file.end);
					asset.size = file.tellg();

					/* Go back to the beginning */
					file.seekg(0, file.beg);

					/* Beg the operating system for some memory */
					asset.buffer = new char[asset.size];

					/* Read the file in */
					file.read(asset.buffer, asset.size);

					if (!file)
						BlowErrorFuse();

					/* Finally close the file */
					file.close();

					/* Add the lazy loaded data into a map */
					lazyloaded_assets_lock.lock();
					lazy_assets[lazy_asset.first] = asset;
					lazy_asset_list.push_back(lazy_asset.first);
					lazyloaded_assets_lock.unlock();
				}
				else
				{
					/* Something went wrong, like file not found etc. */
					BlowErrorFuse();
				}
			});

#else
		/* Read the files sequentially if muiltithreading is disabled */
		for (size_t i = 0; i < lazyload_queue.size(); ++i)
		{
			if (Diagnostics::Debugging::AssetLoading)
				Debug::Log("Loading: " + lazyload_queue[i].first);

			std::ifstream file(Global::FilePaths::Resources + lazyload_queue[i].first, std::ifstream::binary);
			if (file)
			{
				Asset asset;
				asset.type = lazyload_queue[i].second;

				/* Get the file length */
				file.seekg(0, file.end);
				asset.size = file.tellg();

				/* Go back to the beginning */
				file.seekg(0, file.beg);

				/* Beg the operating system for some memory */
				asset.buffer = new char[asset.size];

				/* Read the file in */
				file.read(asset.buffer, asset.size);

				if (!file)
					BlowErrorFuse();

				/* Finally close the file */
				file.close();

				/* Add the lazy loaded data into a map */
				assets[lazyload_queue[i].first] = asset;
				asset_list.push_back(lazyload_queue[i].first);
			}
			else
			{
				/* Something went wrong, like file not found etc. */
				BlowErrorFuse();
			}
		}
#endif

		/* Clear the queue after it has been processed */
		lazyload_queue.clear();

		/* After the asset files have been read in, let SDL turn them into usable data */
		for (size_t i = 0; i < lazy_asset_list.size(); ++i)
		{
			switch (lazy_assets[lazy_asset_list[i]].type)
			{
				case (TEXTURE):
					textures[lazy_asset_list[i]] = Texture(Resources::LoadTextureFromMem(lazy_assets[lazy_asset_list[i]]));
					break;

				default:
					break;
			};
		}

		/* Free the asset list after they have been processed into textures, fonts, sounds etc. */
		FreeBundledAssets();
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

	SDL_RWops* AssetManager::sdl_mem_read_bundle(const std::string& file_path)
	{
		return SDL_RWFromMem(AssetManager::assets[file_path].buffer, AssetManager::assets[file_path].size);
	}

	SDL_RWops* AssetManager::sdl_mem_read(const Asset& asset)
	{
		return SDL_RWFromMem(asset.buffer, asset.size);
	}

	void AssetManager::FreeBundledAssets()
	{
		for (size_t i = 0; i < AssetManager::asset_list.size(); ++i)
		{
			AssetManager::assets[AssetManager::asset_list[i]].Free();
		}
	}

	void AssetManager::Free()
	{
		/* Textures */
		for (auto tex : textures)
			tex.second.Destroy();
		textures.clear();

		/* Fonts have a destructor, so we can just throw them away */
		fonts.clear();

		/* Sounds */
		for (auto sound : sounds)
			sound.second.free();
		sounds.clear();

		/* Music */
		for (auto music : musics)
			music.second.free();
		musics.clear();
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
