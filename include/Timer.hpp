#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <chrono>
#include <string>
#endif

namespace Birb
{
	/// Class for timing things. Accurate down to milliseconds
	class Timer
	{
	public:
		void Start();
		void Stop();
		double ElapsedMilliseconds() const;
		double ElapsedSeconds() const;
		double ElapsedMinutes() const;
		double ElapsedHours() const;

		static double CalcSeconds(const double& mills); 	///< Converts milliseconds into seconds
		static double CalcMinutes(const double& mills); 	///< Converts milliseconds into minutes
		static double CalcHours(const double& mills); 	///< Converts milliseconds into hours

		std::string DigitalFormat() const; ///< Prints the current elapsed time in digital format (00:00:00:000)
		std::string SplitDigitalFormat(const double& previousmills /**< [in] elapsed milliseconds of the previous split */) const; ///< Used for calculating digital time for a split during timing
		bool running = false;

	private:
		std::string DoubleDigitify(const double& value) const;
		std::string TripleDigitify(const double& value) const;
		std::chrono::time_point<std::chrono::steady_clock> startTime;
		std::chrono::time_point<std::chrono::steady_clock> endTime;
	};
}
