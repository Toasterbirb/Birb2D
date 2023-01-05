#include "Timer.hpp"
#include "Logger.hpp"

#ifdef DISTCC
#include <cmath>
#endif

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

	double Timer::ElapsedMilliseconds() const
	{
		std::chrono::time_point<std::chrono::steady_clock> t_endTime;
		if (running)
			t_endTime = std::chrono::steady_clock::now();
		else
			t_endTime = endTime;

		return std::chrono::duration_cast<std::chrono::milliseconds>(t_endTime - startTime).count();
	}

	double Timer::ElapsedSeconds() const
	{
		return ElapsedMilliseconds() / 1000.0;
	}

	double Timer::ElapsedMinutes() const
	{
		return ElapsedSeconds() / 60.0;
	}

	double Timer::ElapsedHours() const
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

	std::string Timer::DoubleDigitify(const double& value) const
	{
		std::string valueString = std::to_string(static_cast<int>(std::floor(value)));

		if (valueString.size() > 2)
			valueString = valueString.substr(valueString.size() - 2, 2);

		if (value < 10.0)
			return "0" + valueString;
		else
			return valueString;
	}

	std::string Timer::TripleDigitify(const double& value) const
	{
		std::string valueString = std::to_string(static_cast<int>(std::floor(value)));

		if (valueString.size() > 3)
			valueString = valueString.substr(valueString.size() - 3, 3);

		if (value < 10.0)
			return "00" + valueString;
		else if (value < 100.0)
			return "0" + valueString;
		else
			return valueString;
	}


	std::string Timer::DigitalFormat() const
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

	std::string Timer::SplitDigitalFormat(const double& previousmills) const
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
}
