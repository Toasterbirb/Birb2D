#include <birb2d/Renderwindow.hpp>
#include <birb2d/Timestep.hpp>

int main(int argc, char** argv)
{
	Birb::Window window("Birb2D project template", Birb::Vector2int(1280, 720), 75, false);
	Birb::TimeStep timeStep;
	timeStep.Init(&window);

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
