#include <SDL.hpp>

#include "Timestep.hpp"
#include "Values.hpp"

namespace Birb
{
	void TimeStep::Init(Window* p_mainWindow)
	{
		currentTime = utils::hireTimeInSeconds();
		mainWindow = p_mainWindow;
	}

	void TimeStep::Start()
	{
		startTick = SDL_GetTicks();

		double newTime = utils::hireTimeInSeconds();
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
		int frameTicks = SDL_GetTicks() - startTick;

		if (frameTicks < 1000 / mainWindow->refresh_rate)
			SDL_Delay(1000 / mainWindow->refresh_rate - frameTicks);
	}
}
