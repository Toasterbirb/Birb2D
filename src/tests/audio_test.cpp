#include "Audio.hpp"
#include "Logger.hpp"
#include "doctest.h"

namespace Birb
{
	TEST_CASE("Audio tests")
	{
		Audio::Init(0);
		Audio::SoundFile sound("./res/audio/game_over.wav");
		Audio::MusicFile music("./res/audio/score.wav");

		Debug::Log("A sound should play now");
		sound.play();
		CHECK(sound.isPlaying());
		SDL_Delay(1000);

		Debug::Log("Another sound should play now");
		music.play();
		CHECK(music.isPlaying());
		SDL_Delay(1000);
	}
}
