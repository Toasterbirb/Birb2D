#include "Stopwatch.hpp"
#include "Logger.hpp"

namespace Birb
{
	Stopwatch::Stopwatch(std::string title)
	:title(title)
	{
		timer.Start();
	}

	void Stopwatch::Stop()
	{
		timer.Stop();

		if (timer.ElapsedSeconds() < 1)
			Debug::Log("[" + title + "] Took " + std::to_string(static_cast<int>(timer.ElapsedMilliseconds())) + "ms");
		else if (timer.ElapsedSeconds() < 60)
			Debug::Log("[" + title + "] Took " + std::to_string(timer.ElapsedSeconds()) + "s");
		else
			Debug::Log("[" + title + "] Took " + std::to_string(timer.ElapsedMinutes()) + "min");
	}
}
