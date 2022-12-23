#include <SDL.hpp>

#include "Timestep.hpp"
#include "Utils.hpp"
#include "Values.hpp"
#include "microprofile.h"

#define PROFILER_GROUP "Timestep"
#define PROFILER_COLOR MP_BLACK

namespace Birb
{
	void TimeStep::Init(Window* p_mainWindow)
	{
		currentTime = utils::hireTimeInSeconds();
		mainWindow = p_mainWindow;
	}

	void TimeStep::Start()
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Begin step", PROFILER_COLOR);
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
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Step delay", PROFILER_COLOR);

		/* Calculate the frame budget usage */
		double current_frame_time = utils::hireTimeInSeconds() - currentTime;
		frame_budget = (current_frame_time / (1.0f / mainWindow->refresh_rate)) * 100;

		/* Stall to reach the fps target */
		int frameTicks = SDL_GetTicks() - startTick;

		if (frameTicks < 1000 / mainWindow->refresh_rate)
			SDL_Delay(1000 / mainWindow->refresh_rate - frameTicks);
	}
}
