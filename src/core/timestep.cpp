#ifdef LIB_SDL
#include <SDL2/SDL.h>
#else
#include <Logger.hpp>
#endif /* LIB_SDL */

#include "Timestep.hpp"
#include "Utils.hpp"
#include "Values.hpp"

namespace Birb
{
	TimeStep::TimeStep()
	{
		currentTime = Utils::hireTimeInSeconds();
	}

	void TimeStep::Start()
	{
#ifdef LIB_SDL
		startTick = SDL_GetTicks();
#else
		Debug::Log("Figure out an alternative for SDL_GetTicks()", Debug::fixme);
#endif /* LIB_SDL */

		double newTime = Utils::hireTimeInSeconds();
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
#ifdef LIB_SDL
		int frameTicks = SDL_GetTicks() - startTick;

		if (frameTicks < 1000 / Global::RenderVars::RefreshRate)
			Utils::Sleep(1000 / Global::RenderVars::RefreshRate - frameTicks);
#else
		Debug::Log("Figure out an alternative for SDL_GetTicks()", Debug::fixme);
#endif /* LIB_SDL */
	}
}
