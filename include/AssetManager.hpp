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
	struct Asset
	{
		//SDL_RWops* sdl_data;
		char* buffer;
		size_t size;
		void Free();
	};

	/// Class for managing and loading assets
	class AssetManager
	{
	public:
		AssetManager(); ///< Initialize and empty asset manager

		static bool InitializeBundledAssets();
#ifdef BUNDLED_ASSETS
		static inline std::map<std::string, Asset> assets;
		static inline std::vector<std::string> asset_list;
		static SDL_RWops* sdl_mem_read(const std::string& file_path);
#endif
		static void FreeBundledAssets();

		/* Textures */
		void AddTexture(const std::string& name, Texture texture);
		void LoadTexture(const std::string& name, const std::string& file_path);
		Texture& texture(const std::string& name);

	private:
		/* Maps for different asset types */
		std::map<std::string, Texture> textures;
		std::map<std::string, Font> fonts;
		std::map<std::string, Audio::SoundFile> sounds;
		std::map<std::string, Audio::MusicFile> musics;
	};
}
