#include "Audio.hpp"
#include "Logger.hpp"
#include "Values.hpp"
#include "doctest.h"

namespace Birb
{
	TEST_CASE("Audio tests")
	{
		Birb::ApplicationInfo appInfo("Birb2D_tests");

		Audio::Init(0);
		Audio::SoundFile sound(appInfo.ResLocation + "/audio/game_over.wav");
		Audio::MusicFile music(appInfo.ResLocation + "/audio/score.wav");

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
