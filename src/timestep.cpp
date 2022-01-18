#include <SDL2/SDL.h>
#include "Timestep.hpp"
#include "Utils.hpp"
#include "Values.hpp"

namespace Birb
{
	void TimeStep::Init()
	{
		currentTime = utils::hireTimeInSeconds();
	}

	void TimeStep::Start()
	{
		startTick = SDL_GetTicks();

		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

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

		if (frameTicks < 1000 / Global::RenderVars::RefreshRate)
			SDL_Delay(1000 / Global::RenderVars::RefreshRate - frameTicks);
	}

	float TimeStep::getTimestepAlpha()
	{
		return accumulator / timeStep;
	}
}
