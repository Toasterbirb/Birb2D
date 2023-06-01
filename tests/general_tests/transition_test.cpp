#include "Color.hpp"
#include "Render.hpp"
#include "Timer.hpp"
#include "Transition.hpp"
#include "Transitions/BlockFade.hpp"
#include "Transitions/Wipe.hpp"
#include "doctest.h"
#include "Game.hpp"
#include "Transitions/Fade.hpp"
#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace Birb;

namespace BirbTest
{
	void transition_start(Game& game);
	void transition_input(Game& game);
	void transition_update(Game& game);
	void transition_render(Game& game);

	BaseTransition* transition;

	/* How long each fade test should last */
	const float test_duration = 1.0f;
	const float confirmation_duration = 0.2f;

	Timer test_timer;

	TEST_CASE("Rendering: Transitions")
	{
		Game::WindowOpts transition_test_win_opts;
		transition_test_win_opts.refresh_rate = 240;
		transition_test_win_opts.title = "Transition animation tests";

		Render::AlphaBlendingToggle(true);

		SUBCASE("Basic fade transition")
		{
			transition = new Transition::Fade(0x000000);
		}

		SUBCASE("Block fade transition")
		{
			transition = new Transition::BlockFade(0x000000, 8);
		}

		SUBCASE("Wipe transition left")
		{
			transition = new Transition::Wipe(0x000000, Transition::LEFT);
		}

		SUBCASE("Wipe transition right")
		{
			transition = new Transition::Wipe(0x000000, Transition::RIGHT);
		}

		SUBCASE("Wipe transition up")
		{
			transition = new Transition::Wipe(0x000000, Transition::UP);
		}

		SUBCASE("Wipe transition down")
		{
			transition = new Transition::Wipe(0x000000, Transition::DOWN);
		}

		transition->set_color(Colors::Nord::Aurora::nord14);

		Game game(transition_test_win_opts, transition_start, transition_input, transition_update, transition_render);
		game.Start();

		CHECK_FALSE(game.ErrorFuseStatus());

		delete transition;

		Render::AlphaBlendingToggle(false);
	}

	void transition_start(Game& game)
	{
		test_timer.Start();
	}

	void transition_input(Game& game)
	{
		if (game.window->isKeyUp())
			game.application_running = false;
	}

	void transition_update(Game& game)
	{
		if (test_timer.ElapsedSeconds() > test_duration + confirmation_duration)
			game.application_running = false;
	}

	void transition_render(Game& game)
	{
		float progress = test_timer.ElapsedSeconds() / test_duration;
		transition->draw(Math::Clamp(progress, 0.0f, 1.0f));
	}
}
