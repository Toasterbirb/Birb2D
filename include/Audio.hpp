#pragma once

#ifndef NO_SOUND

#include "STD.hpp"
#include "SDL.hpp"

namespace Birb
{
	struct Audio
	{
		static bool Init(int flags); ///< Initializes the SDL_mixer library

		/// Set all for volume channels. The volume value should be
		/// between 0 and 1
		static void SetGlobalVolume(float volume_percent);
		static int GetCurrentGlobalVolume();

		/// Used for short sound effects
		class SoundFile
		{
		public:
			SoundFile();
			SoundFile(const std::string& p_filePath);

			/// Play the sound file
			void play();

			/// Free the heap allocated audio file
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
			MusicFile();
			MusicFile(const std::string& p_filePath);

			/// Play the music file
			void play();

			/// Play the music file with the option of looping it
			void play(bool loop);

			/// Free the heap allocated music file
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
#endif /* NO_SOUND */
