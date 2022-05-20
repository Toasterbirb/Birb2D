#pragma once

#ifndef NO_SOUND
#include <iostream>

#ifdef LIB_SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif /* LIB_SDL */

namespace Birb
{
	struct Audio
	{
		static bool Init(int flags); ///< Initializes the SDL_mixer library

		/// Used for short sound effects
		class SoundFile
		{
		public:
			SoundFile(const std::string& p_filePath);
			void play();
			void free()
			{
#ifdef LIB_SDL
				Mix_FreeChunk(sound);
#endif /* LIB_SDL */
			}
			bool isPlaying();

			~SoundFile()
			{
				/* Free the soundfile when its destroyed */
				free();
			}
		private:
#ifdef LIB_SDL
			Mix_Chunk* sound;
#endif /* LIB_SDL */
			std::string filePath;
		};

		/// Used for longer audio pieces like music. Shouldn't be used for sound effects
		class MusicFile
		{
		public:
			MusicFile(const std::string& p_filePath);
			void play();
			void play(bool loop);
			void free()
			{
#ifdef LIB_SDL
				Mix_FreeMusic(music);
#endif /* LIB_SDL */
			}
			bool isPlaying();

			~MusicFile()
			{
				/* Free the musicfile when its destroyed */
				free();
			}
		private:
#ifdef LIB_SDL
			Mix_Music* music;
#endif /* LIB_SDL */
			std::string filePath;
		};
	};
}
#endif /* NO_SOUND */
