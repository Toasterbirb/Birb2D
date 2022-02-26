#include <SDL2/SDL.h>
#include "Timer.hpp"
#include "Logger.hpp"
#include "doctest.h"

namespace Birb
{
	void Timer::Start()
	{
		startTime = std::chrono::steady_clock::now();
		running = true;
	}

	void Timer::Stop()
	{
		endTime = std::chrono::steady_clock::now();
		running = false;
	}

	double Timer::ElapsedMilliseconds()
	{
		std::chrono::time_point<std::chrono::steady_clock> t_endTime;
		if (running)
			t_endTime = std::chrono::steady_clock::now();
		else
			t_endTime = endTime;

		return std::chrono::duration_cast<std::chrono::milliseconds>(t_endTime - startTime).count();
	}

	double Timer::ElapsedSeconds()
	{
		return ElapsedMilliseconds() / 1000.0;
	}

	double Timer::ElapsedMinutes()
	{
		return ElapsedSeconds() / 60.0;
	}

	double Timer::ElapsedHours()
	{
		return ElapsedMinutes() / 60.0;
	}

	double Timer::CalcSeconds(const double& mills)
	{
		return mills / 1000.0;
	}

	double Timer::CalcMinutes(const double& mills)
	{
		return mills / 1000.0 / 60.0;
	}

	double Timer::CalcHours(const double& mills)
	{
		return mills / 1000.0 / 60.0 / 60.0;
	}

	TEST_CASE("Timer format conversions")
	{
		int milliseconds = 3600000;

		CHECK(Birb::Timer::CalcSeconds(milliseconds) == 3600);
		CHECK(Birb::Timer::CalcMinutes(milliseconds) == 60);
		CHECK(Birb::Timer::CalcHours(milliseconds) == 1);
	}

	std::string DoubleDigitify(const double& value)
	{
		std::string valueString = std::to_string((int)std::floor(value));

		if (valueString.size() > 2)
			valueString = valueString.substr(valueString.size() - 2, 2);

		if (value < 10.0)
			return "0" + valueString;
		else
			return valueString;
	}

	std::string TripleDigitify(const double& value)
	{
		std::string valueString = std::to_string((int)std::floor(value));

		if (valueString.size() > 3)
			valueString = valueString.substr(valueString.size() - 3, 3);

		if (value < 10.0)
			return "00" + valueString;
		else if (value < 100.0)
			return "0" + valueString;
		else
			return valueString;
	}


	std::string Timer::DigitalFormat()
	{
		/* Return default 00:00:00:000 if timer is not running */
		if (!running && ElapsedMilliseconds() == 0)
			return "00:00:00:000";

		double elapsedMilliseconds 	= ElapsedMilliseconds();
		double elapsedHours 		= ElapsedHours();
		double elapsedMinutes 		= ElapsedMinutes() - (std::floor(ElapsedHours()) * 60);
		double elapsedSeconds 		= ElapsedSeconds() - (std::floor(ElapsedMinutes()) * 60);

		std::string hourValue 			= DoubleDigitify(elapsedHours);
		std::string minuteValue 		= DoubleDigitify(elapsedMinutes);
		std::string secondValue 		= DoubleDigitify(elapsedSeconds);
		std::string millisecondValue 	= TripleDigitify(elapsedMilliseconds);

		std::string digital_string = hourValue + ":" + minuteValue + ":" + secondValue + ":" + millisecondValue;
		return digital_string;
	}

	std::string Timer::SplitDigitalFormat(const double& previousmills)
	{
		/* Return default 00:00 if time hasn't passed */
		if (!running && ElapsedMilliseconds() == 0)
			return "00:00";

		double elapsedMilliseconds 	= ElapsedMilliseconds() - previousmills;
		double elapsedMinutes 		= std::floor(CalcMinutes(elapsedMilliseconds));
		double elapsedSeconds 		= std::floor(CalcSeconds(elapsedMilliseconds)) - (elapsedMinutes * 60);

		std::string minuteValue 		= DoubleDigitify(elapsedMinutes);
		std::string secondValue 		= DoubleDigitify(elapsedSeconds);
		std::string millisecondValue 	= TripleDigitify(elapsedMilliseconds);

		std::string digital_string = minuteValue + ":" + secondValue;
		return digital_string;
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
