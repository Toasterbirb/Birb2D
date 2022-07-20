#ifdef LIB_SDL
#include <SDL.h>
#else
#include <Logger.hpp>
#endif /* LIB_SDL */

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
#ifdef LIB_SDL
		startTick = SDL_GetTicks();
#else
		Debug::Log("Figure out an alternative for SDL_GetTicks()", Debug::fixme);
#endif /* LIB_SDL */

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
#ifdef LIB_SDL
		int frameTicks = SDL_GetTicks() - startTick;

		if (frameTicks < 1000 / mainWindow->refresh_rate)
			SDL_Delay(1000 / mainWindow->refresh_rate - frameTicks);
#else
		Debug::Log("Figure out an alternative for SDL_GetTicks() and SDL_Delay()", Debug::fixme);
#endif /* LIB_SDL */
	}
}
