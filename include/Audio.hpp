#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Audio
{
public:
	bool initAudio(int flags);
};

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
