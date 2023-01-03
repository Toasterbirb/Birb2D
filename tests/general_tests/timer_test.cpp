#include <thread>
#include "doctest.h"
#include "Logger.hpp"
#include "Timer.hpp"

using namespace Birb;

namespace BirbTest
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
		std::this_thread::sleep_for(1200ms);
		timer.Stop();

		CHECK(timer.ElapsedSeconds() == 1.20);
		CHECK(timer.DigitalFormat() == "00:00:01:200"); /* Test digital format since we have already spent time on timing */

		/* Make sure the timer actually stops after stopping it */
		Debug::Log("Delaying for 100 milliseconds to see if the timer stopped");
		std::this_thread::sleep_for(100ms);
		CHECK(timer.ElapsedSeconds() == 1.20);
	}

	TEST_CASE("Timer accuracy test")
	{
		using namespace std::chrono_literals;

		Birb::Timer timer;
		Debug::Log("Delay test for 123 milliseconds");
		timer.Start();
		std::this_thread::sleep_for(123ms);
		timer.Stop();

		CHECK(timer.ElapsedMilliseconds() == 123);
	}
}
