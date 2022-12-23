#pragma once

#include "Renderwindow.hpp"
#include <vector>

namespace Birb
{
	/// Limit the runtime speed and handle delta time
	class TimeStep
	{
	public:
		/* Functions */
		void Init(Window* p_mainWindow); 	///< Reset the currentTime variable
		void Start(); 	///< Start a new step. Call this in the beginning of the gameloop
		bool Running(); ///< Check if the accumulator is empty yet. While this is true, handle input events etc.
		void Step(); 	///< Deplete the accumulator. Speed determined by the value of timeStep
		void End(); 	///< End the timeStep and delay the rendering to stay within the refreshrate
		//float deltaTime(); ///< Method to get deltatime

		/* Variables */
		Window* mainWindow;
		const double timeStep = 0.01;
		double accumulator = 0.00;
		double currentTime;
		float deltaTime;
		int startTick;

		/// A percentage value that represents the average amount
		/// of frame budget used before the frametime exceeds the FPS target
		double FrameBudget() const;

	private:
		size_t frame_budget_avg_counter = 0;
		std::vector<double> frame_budget_values;
	};
}
