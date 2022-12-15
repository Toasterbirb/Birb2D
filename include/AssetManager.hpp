#pragma once
#include "STD.hpp"
#include "Font.hpp"
#include "Texture.hpp"
#include "Audio.hpp"

#ifdef BUNDLED_ASSETS
#include "zip.h"
#endif

namespace Birb
{
	/// Object that contains the data for individual assets in a asset bundle
	struct Asset
	{
		char* buffer;
		size_t size;
		void Free();
	};

	/// Class for managing and loading assets
	class AssetManager
	{
	public:
		AssetManager(); ///< Initialize and empty asset manager

		/// Extract and read bundled assets if they have been compiled with the application
		static bool InitializeBundledAssets();
#ifdef BUNDLED_ASSETS
		/// Dictionary of asset objects with the asset name as the key
		static inline std::map<std::string, Asset> assets;

		/// List of asset names
		static inline std::vector<std::string> asset_list;

		/// Read asset data at given relative path in bundled assets
		static SDL_RWops* sdl_mem_read(const std::string& file_path);
#endif
		/// Free all heap allocated asset objects
		static void FreeBundledAssets();

		/** Textures **/
		/// Add a texture into the asset manager
		void AddTexture(const std::string& name, Texture texture);

		/// Load a texture from file path into the asset manager
		void LoadTexture(const std::string& name, const std::string& file_path);

		/// Access a texture in the asset manager
		Texture& texture(const std::string& name);

	private:
		/* Maps for different asset types */
		std::map<std::string, Texture> textures;
		std::map<std::string, Font> fonts;
		std::map<std::string, Audio::SoundFile> sounds;
		std::map<std::string, Audio::MusicFile> musics;
	};
}
