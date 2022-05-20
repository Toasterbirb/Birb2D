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

#ifdef LIB_SDL
        CHECK_FALSE(Global::IsInit::SDL_mixer);
#endif /* LIB_SDL */
		Audio::SoundFile sound(appInfo.ResLocation + "/audio/game_over.wav");
        // FIXME: Global is not being updated properly
		
#ifdef LIB_SDL
        CHECK(Global::IsInit::SDL_mixer);
#endif /* LIB_SDL */

		Audio::MusicFile music(appInfo.ResLocation + "/audio/score.wav");

		Debug::Log("A sound should play now");
		sound.play();
		CHECK(sound.isPlaying());
#ifdef LIB_SDL
		SDL_Delay(1000);
#endif /* LIB_SDL */

		Debug::Log("Another sound should play now");
		music.play();
		CHECK(music.isPlaying());

#ifdef LIB_SDL
		SDL_Delay(1000);
#endif /* LIB_SDL */

		/* De-initialize SDL_mixer */
#ifdef LIB_SDL
		Mix_Quit();
#endif /* LIB_SDL */
	}
}
#endif /* NO_SOUND */
