#pragma once
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace Birb
{
	struct Audio
	{
		static bool Init(int flags); ///< Initializes the SDL_mixer library

		/// Used for short sound effects
		class SoundFile
		{
		public:
			SoundFile(std::string p_filePath);
			void play();
			void free()
			{
				Mix_FreeChunk(sound);
			}
			bool isPlaying();
		private:
			Mix_Chunk* sound;
			std::string filePath;
		};

		/// Used for longer audio pieces like music. Shouldn't be used for sound effects
		class MusicFile
		{
		public:
			MusicFile(std::string p_filePath);
			void play();
			void play(bool loop);
			void free()
			{
				Mix_FreeMusic(music);
			}
			bool isPlaying();
		private:
			Mix_Music* music;
			std::string filePath;
		};
	};

}
