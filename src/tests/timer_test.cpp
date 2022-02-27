#include "doctest.h"
#include <SDL2/SDL.h>
#include "Logger.hpp"
#include "Timer.hpp"

namespace Birb
{
	TEST_CASE("Timer format conversions")
	{
		int milliseconds = 3600000;

		CHECK(Birb::Timer::CalcSeconds(milliseconds) == 3600);
		CHECK(Birb::Timer::CalcMinutes(milliseconds) == 60);
		CHECK(Birb::Timer::CalcHours(milliseconds) == 1);
	}

	TEST_CASE("Timer stop test")
	{
		Birb::Debug::Log("Running timer tests, this might take a moment...");
		Birb::Timer timer;
		timer.Start();
		CHECK(timer.running);
		SDL_Delay(1200);
		timer.Stop();

		CHECK(timer.ElapsedSeconds() == 1.20);
		CHECK(timer.DigitalFormat() == "00:00:01:200"); /* Test digital format since we have already spent time on timing */

		/* Make sure the timer actually stops after stopping it */
		SDL_Delay(500);
		CHECK(timer.ElapsedSeconds() == 1.20);
	}

	TEST_CASE("Timer accuracy test")
	{
		Birb::Timer timer;
		timer.Start();
		SDL_Delay(123);
		timer.Stop();

		CHECK(timer.ElapsedMilliseconds() == 123);
	}
}
