#include "Birb2D.hpp"

int main(void)
{
	Birb::Debug::Log("Creating the window");
	Birb::Window window("Birb2D project template", Birb::Vector2Int(1280, 720), 75, false);
	Birb::TimeStep timeStep;
	timeStep.Init(&window);

	Birb::Debug::Log("Starting the game loop");
	bool ApplicationRunning = true;
	while (ApplicationRunning)
	{
		timeStep.Start();
		while (timeStep.Running())
		{
			/* Handle input stuff */
			while (window.PollEvents())
			{
				window.EventTick(window.event, &ApplicationRunning);
			}

			timeStep.Step();
		}

		window.Clear();
		/* Handle rendering */



		/* End of rendering */
		window.Display();

		timeStep.End();
	}

	return 0;
}
