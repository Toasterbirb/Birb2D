#ifndef NO_SOUND
#include "Audio.hpp"
#include "Logger.hpp"
#include "Values.hpp"
#include "Diagnostics.hpp"

namespace Birb
{
	//** Initializes the SDL_mixer library. Needs to be called before any other audio features are used
	bool Audio::Init(int flags)
	{
#ifdef LIB_SDL
		if (Global::IsInit::SDL_mixer)
			return true;

#ifdef DEBUG
		if (Diagnostics::Debugging::InitMessages)
			Debug::Log("Initializing audio...");
#endif /* DEBUG */

		int initted = Mix_Init(flags);
		if ((initted&flags) != flags)
		{
			// Something went wrong
			Debug::Log("Error initializing SDL_mixer: " + (std::string)Mix_GetError(), Debug::error);
			return false;
		}

		if (SDL_Init(SDL_INIT_AUDIO) > 0)
		{
			Debug::Log("Error initializing SDL_INIT_AUDIO: " + (std::string)SDL_GetError(), Debug::error);
			return false;
		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
		{
			Debug::Log("Error during Mix_OpenAudio: " + (std::string)Mix_GetError(), Debug::error);
			return false;
		}

		// Audio initialization was successful
#ifdef DEBUG
		if (Diagnostics::Debugging::InitMessages)
			Debug::Log("Audio initialized successfully!");
#endif /* DEBUG */

		Global::IsInit::SDL_mixer = true;
#else /* LIB_SDL */
		Debug::Log("Audio not implemented without SDL_mixer!", Debug::fixme);
#endif /* LIB_SDL */
		return true;
	}

	//** Loads up a music file from given path. Shouldn't be used for short sound effects
	Audio::MusicFile::MusicFile(const std::string& p_filePath)
	:filePath(p_filePath)
	{
		Audio::Init(0);
#ifdef LIB_SDL
		music = Mix_LoadMUS(p_filePath.c_str());
		if (!music)
		{
			Debug::Log("Error loading music file [" + p_filePath + "] Error: " + (std::string)Mix_GetError(), Debug::error);
			return;
		}
#endif /* LIB_SDL */
	}

	//** Loads up a sound file from given path. Used for shorter sound effects and not music
	Audio::SoundFile::SoundFile(const std::string& p_filePath)
	:filePath(p_filePath)
	{
		Audio::Init(0);
#ifdef LIB_SDL
		sound = Mix_LoadWAV(p_filePath.c_str());
		if (!sound)
		{
			Debug::Log("Error loading sound file [" + p_filePath + "] Error: " + (std::string)Mix_GetError(), Debug::error);
			return;
		}
#endif /* LIB_SDL */
	}

	void Audio::MusicFile::play(bool loop)
	{
		int loopValue;
		if (loop)
			loopValue = -1;
		else
			loopValue = 0;

#ifdef LIB_SDL
		if (Mix_PlayMusic(music, loopValue) == -1)
		{
			Debug::Log("Error playing music file [" + filePath + "] Error: " + Mix_GetError(), Debug::error);
		}
#endif /* LIB_SDL */
	}

	void Audio::MusicFile::play()
	{
#ifdef LIB_SDL
		if (Mix_PlayMusic(music, 0) == -1)
		{
			Debug::Log("Error playing music file [" + filePath + "] Error: " + (std::string)Mix_GetError(), Debug::error);
		}
#endif /* LIB_SDL */
	}

	void Audio::SoundFile::play()
	{
#ifdef LIB_SDL
		if (Mix_PlayChannel(-1, sound, 0) == -1)
		{
			Debug::Log("Error playing sound file [" + filePath + "] Error: " + (std::string)Mix_GetError(), Debug::error);
		}
#endif /* LIB_SDL */
	}

	bool Audio::MusicFile::isPlaying()
	{
#ifdef LIB_SDL
		if (Mix_PlayingMusic())
			return true;
		else
			return false;
#else
		return false;
#endif /* LIB_SDL */
	}

	bool Audio::SoundFile::isPlaying()
	{
#ifdef LIB_SDL
		if (Mix_Playing(-1) > 0)
			return true;
		else
			return false;
#else
		return false;
#endif /* LIB_SDL */
	}
}
#endif /* NO_SOUND */
