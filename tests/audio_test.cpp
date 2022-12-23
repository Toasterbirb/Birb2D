#ifndef NO_SOUND
#include "Audio.hpp"
#include "Logger.hpp"
#include "Values.hpp"
#include "doctest.h"

namespace Birb
{
	TEST_CASE("Audio tests")
	{
        CHECK_FALSE(Global::IsInit::SDL_mixer);

		Audio::SoundFile sound("audio/game_over.wav");

        CHECK(Global::IsInit::SDL_mixer);

		Audio::MusicFile music("audio/score.wav");

		Debug::Log("A sound should play now");
		sound.play();
		CHECK(sound.isPlaying());
		SDL_Delay(1000);

		Debug::Log("Another sound should play now");
		music.play();
		CHECK(music.isPlaying());

		SDL_Delay(1000);

		/* De-initialize SDL_mixer and free the sound files */
		sound.free();
		music.free();
		Mix_Quit();
		Global::IsInit::SDL_mixer = false;
	}
}
#endif /* NO_SOUND */
