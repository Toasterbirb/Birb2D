#include "Diagnostics.hpp"
#include "SDL_ttf.h"
#include "Timestep.hpp"
#include "Timer.hpp"
#include "Scene.hpp"
#include "Renderwindow.hpp"
#include "Vector/Vector2Int.hpp"
#include "doctest.h"

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Rendering: Frametime graph")
	{
		/* Initialize fonts */
		TTF_Init();

		{
			Window window("Frametime test", Vector2Int(1280, 720), 60, false);

			TimeStep timeStep;
			timeStep.Init(&window);

			Diagnostics::FrametimeGraph graph(Rect(32, 32, 400, 150), 200, timeStep);
			CHECK(graph.pointCount == 200);
			CHECK(graph.enabled == true);
			CHECK(graph.font.isLoaded() == true);

			Timer testTimer;
			testTimer.Start();

			bool ApplicationRunning = true;
			while (ApplicationRunning)
			{
				if (testTimer.ElapsedSeconds() > 1.0f)
					ApplicationRunning = false;

				timeStep.Start();
				while (timeStep.Running())
				{
					while (window.PollEvents())
					{
						window.EventTick(window.event, &ApplicationRunning);
					}

					timeStep.Step();
				}

				window.Clear();
				/** Handle rendering **/

				graph.Render();

				/** End of rendering **/
				window.Display();
				timeStep.End();
			}
		}

		/* Nuke fonts */
		TTF_Quit();
	}
}
