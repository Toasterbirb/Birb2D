#include "Timestep.hpp"
#include "Utils.hpp"
#include "Values.hpp"

namespace Birb
{
	TimeStep::TimeStep()
	{
		currentTime = tickTimer.ElapsedSeconds();
		tickTimer.Start();
	}

	void TimeStep::Start()
	{
		startTick = tickTimer.ElapsedMilliseconds();

		double newTime = tickTimer.ElapsedSeconds();
		double frameTime = newTime - currentTime;
		deltaTime = frameTime;

		if (frameTime > 0.25f)
			frameTime = 0.25f;

		currentTime = newTime;
		accumulator += frameTime;
	}

	bool TimeStep::Running()
	{
		return (accumulator >= timeStep);
	}

	void TimeStep::Step()
	{
		accumulator -= timeStep;
	}

	void TimeStep::End()
	{
		int frameTicks = tickTimer.ElapsedMilliseconds() - startTick;

		if (frameTicks < 1000 / Global::RenderVars::RefreshRate)
			Utils::Sleep(1000 / Global::RenderVars::RefreshRate - frameTicks);
	}
}
