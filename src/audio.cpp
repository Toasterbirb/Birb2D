#include <iostream>
#include "../include/Audio.hpp"

bool Audio::initAudio(int flags)
{
	int initted = Mix_Init(flags);
	if ((initted&flags) != flags)
	{
		// Something went wrong
		std::cout << "Error initializing SDL_mixer: " << Mix_GetError() << std::endl;
		return false;
	}

	if (SDL_Init(SDL_INIT_AUDIO) > 0)
	{
		std::cout << "Error initializing SDL_INIT_AUDIO: " << SDL_GetError() << std::endl;
		return false;
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
	{
		std::cout << "Error during Mix_OpenAudio: " << Mix_GetError() << std::endl;
	}

	// Audio initialization was successful
	return true;
}

MusicFile::MusicFile(std::string p_filePath)
:filePath(p_filePath)
{
	music = Mix_LoadMUS(p_filePath.c_str());
	if (!music)
	{
		std::cout << "Error loading music file [" << p_filePath << "] Error: " << Mix_GetError() << std::endl;
		return;
	}
}

SoundFile::SoundFile(std::string p_filePath)
:filePath(p_filePath)
{
	sound = Mix_LoadWAV(p_filePath.c_str());
	if (!sound)
	{
		std::cout << "Error loading sound file [" << p_filePath << "] Error: " << Mix_GetError() << std::endl;
		return;
	}
}

void MusicFile::play(bool loop)
{
	int loopValue;
	if (loop)
		loopValue = -1;
	else
		loopValue = 0;

	if (Mix_PlayMusic(music, loopValue) == -1)
	{
		std::cout << "Error playing music file [" << filePath << "] Error: " << Mix_GetError() << std::endl;
	}
}

void MusicFile::play()
{
	if (Mix_PlayMusic(music, 0) == -1)
	{
		std::cout << "Error playing music file [" << filePath << "] Error: " << Mix_GetError() << std::endl;
	}
}

void SoundFile::play()
{
	if (Mix_PlayChannel(-1, sound, 0) == -1)
	{
		std::cout << "Error playing sound file [" << filePath << "] Error: " << Mix_GetError() << std::endl;
	}
}

bool MusicFile::isPlaying()
{
	if (Mix_PlayingMusic())
		return true;
	else
		return false;
}

bool SoundFile::isPlaying()
{
	if (Mix_Playing(-1) > 0)
		return true;
	else
		return false;
}
