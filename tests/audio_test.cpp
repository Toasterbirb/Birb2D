#ifndef NO_SOUND
#include "Audio.hpp"
#include "Logger.hpp"
#include "Values.hpp"
#include "doctest.h"

namespace Birb
{
	TEST_CASE("Audio tests")
	{
		Birb::ApplicationInfo appInfo("Birb2D_tests");

        CHECK_FALSE(Global::IsInit::SDL_mixer);
		Audio::SoundFile sound(appInfo.ResLocation + "/audio/game_over.wav");
        // FIXME: Global is not being updated properly

        CHECK(Global::IsInit::SDL_mixer);

		Audio::MusicFile music(appInfo.ResLocation + "/audio/score.wav");

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
	}
}
#endif /* NO_SOUND */
