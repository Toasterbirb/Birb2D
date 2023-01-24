#pragma once

#include "ErrorFuse.hpp"
#include <tuple>
#ifndef DISTCC
#include "STD.hpp"
#else
#include <vector>
#include <unordered_map>

#if BIRB_MT == 1
#include <mutex>
#endif /* BIRB_MT */

#endif /* DISTCC */

#include "Font.hpp"
#include "Texture.hpp"
#include "Audio.hpp"

#ifdef BUNDLED_ASSETS
#include "zip.h"
#endif

namespace Birb
{
	enum AssetType
	{
		TEXTURE = 0,
		FONT 	= 1,
		SOUND 	= 2,
		MUSIC 	= 3,
	};

	/// Object that contains the data for individual assets in a asset bundle
	struct Asset
	{
		char* buffer;
		size_t size;
		AssetType type;
		void Free();
	};

	/// Class for managing and loading assets
	class AssetManager : public ErrorFuse
	{
	public:
		AssetManager(); ///< Initialize and empty asset manager

		/// Extract and read bundled assets if they have been compiled with the application
		static bool InitializeBundledAssets();

		/// Read asset data at given relative path in bundled assets
		static SDL_RWops* sdl_mem_read_bundle(const std::string& file_path);

		/// Read asset data into SDL_RWops given an asset object
		static SDL_RWops* sdl_mem_read(const Asset& asset);

		/// Free all heap allocated asset objects
		static void FreeBundledAssets();

		/// Free all assets (doesn't touch bundled assets)
		void Free();

		/** Lazy loading assets **/
		/// Add an asset to a queue to be lazy loaded
		/// If multithreading is disabled, everything will be loaded
		/// sequentially
		void LazyLoadQueue(const std::string& file_path, AssetType type);

		/// Start going trough the lazy loading queue
		void LazyLoad();

		/** Textures **/
		/// Add a texture into the asset manager
		void AddTexture(const std::string& name, Texture texture);

		/// Load a texture from file path into the asset manager
		void LoadTexture(const std::string& name, const std::string& file_path);

		/// Access a texture in the asset manager
		Texture& texture(const std::string& name);

	private:
		/// Dictionary of asset objects with the asset name as the key
		static inline std::unordered_map<std::string, Asset> assets;

		/// List of asset names
		static inline std::vector<std::string> asset_list;

		/* Lazy loading variables */
		std::vector<std::pair<std::string, AssetType>> lazyload_queue;
		static inline std::unordered_map<std::string, Asset> lazy_assets;
		static inline std::vector<std::string> lazy_asset_list;

#if BIRB_MT == 1
		std::mutex lazyloaded_assets_lock;
#endif

		/* Maps for different asset types */
		std::unordered_map<std::string, Texture> textures;
		std::unordered_map<std::string, Font> fonts;
		std::unordered_map<std::string, Audio::SoundFile> sounds;
		std::unordered_map<std::string, Audio::MusicFile> musics;
	};
}
