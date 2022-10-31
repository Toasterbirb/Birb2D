#pragma once
#include <map>
#include <string>

#include "Font.hpp"
#include "Texture.hpp"
#include "Audio.hpp"

namespace Birb
{
	/// Class for managing and loading assets
	class AssetManager
	{
	public:
		AssetManager(); ///< Initialize and empty asset manager

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
