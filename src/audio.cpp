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
			Debug::Log("Error initializing SDL_mixer: " + static_cast<std::string>(Mix_GetError()), Debug::error);
			return false;
		}

		if (SDL_Init(SDL_INIT_AUDIO) > 0)
		{
			Debug::Log("Error initializing SDL_INIT_AUDIO: " + static_cast<std::string>(SDL_GetError()), Debug::error);
			return false;
		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
		{
			Debug::Log("Error during Mix_OpenAudio: " + static_cast<std::string>(Mix_GetError()), Debug::error);
			return false;
		}

		// Audio initialization was successful
#ifdef DEBUG
		if (Diagnostics::Debugging::InitMessages)
			Debug::Log("Audio initialized successfully!");
#endif /* DEBUG */

		Global::IsInit::SDL_mixer = true;
		return true;
	}

	Audio::MusicFile::MusicFile()
	{}

	//** Loads up a music file from given path. Shouldn't be used for short sound effects
	Audio::MusicFile::MusicFile(const std::string& p_filePath)
	:filePath(p_filePath)
	{
		Audio::Init(0);
		music = Mix_LoadMUS(p_filePath.c_str());
		if (!music)
		{
			Debug::Log("Error loading music file [" + p_filePath + "] Error: " + static_cast<std::string>(Mix_GetError()), Debug::error);
			return;
		}
	}

	Audio::SoundFile::SoundFile()
	{}

	//** Loads up a sound file from given path. Used for shorter sound effects and not music
	Audio::SoundFile::SoundFile(const std::string& p_filePath)
	:filePath(p_filePath)
	{
		Audio::Init(0);
		sound = Mix_LoadWAV(p_filePath.c_str());
		if (!sound)
		{
			Debug::Log("Error loading sound file [" + p_filePath + "] Error: " + static_cast<std::string>(Mix_GetError()), Debug::error);
			return;
		}
	}

	void Audio::MusicFile::play(bool loop)
	{
		int loopValue;
		if (loop)
			loopValue = -1;
		else
			loopValue = 0;

		if (Mix_PlayMusic(music, loopValue) == -1)
		{
			Debug::Log("Error playing music file [" + filePath + "] Error: " + Mix_GetError(), Debug::error);
		}
	}

	void Audio::MusicFile::play()
	{
		if (Mix_PlayMusic(music, 0) == -1)
		{
			Debug::Log("Error playing music file [" + filePath + "] Error: " + static_cast<std::string>(Mix_GetError()), Debug::error);
		}
	}

	void Audio::SoundFile::play()
	{
		if (Mix_PlayChannel(-1, sound, 0) == -1)
		{
			Debug::Log("Error playing sound file [" + filePath + "] Error: " + static_cast<std::string>(Mix_GetError()), Debug::error);
		}
	}

	bool Audio::MusicFile::isPlaying()
	{
		if (Mix_PlayingMusic())
			return true;
		else
			return false;
	}

	bool Audio::SoundFile::isPlaying()
	{
		if (Mix_Playing(-1) > 0)
			return true;
		else
			return false;
	}
}
#endif /* NO_SOUND */
