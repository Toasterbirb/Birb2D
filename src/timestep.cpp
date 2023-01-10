#include "SDL.hpp"
#include "STD.hpp"

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

		/* Use the target fps as the amount of samples
		 * for the frame budget average calculation */
		frame_budget_values = std::vector<double>(mainWindow->refresh_rate);

		/* Set fixed update frequency to 25fps by default */
		fixedUpdateFrequency = 25;
		fixedUpdateAccumulator = 0;
	}

	void TimeStep::Start()
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Begin step", PROFILER_COLOR);
		startTick = SDL_GetTicks();

		double newTime = utils::hireTimeInSeconds();
		double frameTime = newTime - currentTime;
		deltaTime = frameTime;

		/* Increment the fixed update accumulator with the new deltatime */
		fixedUpdateAccumulator += deltaTime;

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
		frame_budget_values[frame_budget_avg_counter] = (current_frame_time / (1.0f / mainWindow->refresh_rate)) * 100;

		if (frame_budget_avg_counter < frame_budget_values.size() - 1)
			++frame_budget_avg_counter;
		else
			frame_budget_avg_counter = 0;

		/* Stall to reach the fps target */
		int frameTicks = SDL_GetTicks() - startTick;

		if (frameTicks < 1000 / mainWindow->refresh_rate)
			SDL_Delay(1000 / mainWindow->refresh_rate - frameTicks);
	}

	bool TimeStep::ShouldRunFixedUpdate()
	{
		bool result = (1 / deltaTime) * fixedUpdateFrequency > fixedUpdateAccumulator;

		if (result == true)
			fixedUpdateAccumulator = 0.0f;

		return result;
	}

	double TimeStep::FrameBudget() const
	{
		double frame_budget = 0.00;

		/* Calculate the average */
		for (size_t i = 0; i < frame_budget_values.size(); ++i)
			frame_budget += frame_budget_values[i];

		frame_budget /= frame_budget_values.size();
		return frame_budget;
	}
}
