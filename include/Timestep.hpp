#pragma once

namespace Birb2D
{
	struct TimeStep
	{
		/* Functions */
		void Init();
		void Start();
		bool Running();
		void Step();
		void End();
		float getTimestepAlpha();

		/* Variables */
		const float timeStep = 0.01f;
		float accumulator = 0.01f;
		float currentTime;
		int startTick;
	};
}
