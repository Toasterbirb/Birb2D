#pragma once
#include "STD.hpp"
#include "Timer.hpp"

namespace Birb
{
	/// Class for timing stuff for debuggin purposes
	class Stopwatch
	{
	public:
		Stopwatch(std::string title);
		void Stop();

	private:
		Timer timer;
		std::string title;
	};
}
