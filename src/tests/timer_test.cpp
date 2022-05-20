#include "doctest.h"
#include "Logger.hpp"
#include "Timer.hpp"
#include "Utils.hpp"

namespace Birb
{
	TEST_CASE("Timer format conversions")
	{
		int milliseconds = 3600000;

		CHECK(Timer::CalcSeconds(milliseconds) == 3600);
		CHECK(Timer::CalcMinutes(milliseconds) == 60);
		CHECK(Timer::CalcHours(milliseconds) == 1);
	}

	TEST_CASE("Timer stop test")
	{
		using namespace std::chrono_literals;

		Debug::Log("Running timer tests, this might take a moment...");
		Timer timer;
		Debug::Log("Delay test for 1200 milliseconds");
		timer.Start();
		CHECK(timer.running);
		Utils::Sleep(1200);
		timer.Stop();

		CHECK(timer.ElapsedSeconds() == 1.20);
		CHECK(timer.DigitalFormat() == "00:00:01:200"); /* Test digital format since we have already spent time on timing */

		/* Make sure the timer actually stops after stopping it */
		Debug::Log("Delaying for 500 milliseconds to see if the timer stopped");
		Utils::Sleep(1200);
		CHECK(timer.ElapsedSeconds() == 1.20);
	}

	TEST_CASE("Timer accuracy test")
	{
		using namespace std::chrono_literals;

		Birb::Timer timer;
		Debug::Log("Delay test for 123 milliseconds");
		timer.Start();
		Utils::Sleep(123);
		timer.Stop();

		CHECK(timer.ElapsedMilliseconds() == 123);
	}
}
