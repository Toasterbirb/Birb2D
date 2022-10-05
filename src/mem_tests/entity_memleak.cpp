#include "Renderwindow.hpp"
#include "Timestep.hpp"
#include "Timer.hpp"
#include "Texture.hpp"
#include "Random.hpp"
#include "Scene.hpp"
#include "Logger.hpp"

using namespace Birb;

int main(int argc, char** argv)
{
	bool entityEnabled = true;
	float maxtime = 10;
	if (argc > 1)
		maxtime = atoi(argv[1]);

	if (argc > 2)
	{
		if (strcmp(argv[2], "no_entity") == 0)
		{
			Debug::Log("Skipping entity test");
			entityEnabled = false;
		}
		else
		{
			Debug::Log("Entity enabled");
			entityEnabled = true;
		}
	}
	else
		Debug::Log("The entity test part can be skipped with 'no_entity' flag after the duration");

	Window window("Entity memleak test", Birb::Vector2Int(128, 128), 75, false);
	TimeStep timeStep;
	timeStep.Init(&window);

	Scene scene;
	Texture texture("./res/textures/birb.png");
	Font font;
	font.LoadFont("./res/fonts/freefont/FreeMono.ttf");
	Random rand;

	/* Only run the test for certain amount of seconds */
	Debug::Log("Running the test for " + utils::CleanDecimals(maxtime) + " seconds...");
	int frameCounter = 0;

	Timer timer;
	timer.Start();


	bool ApplicationRunning = true;
	while (ApplicationRunning)
	{
		timeStep.Start();
		while (timeStep.Running())
		{
			/* Handle some input stuff */
			while (window.PollEvents())
			{
				window.EventTick(window.event, &ApplicationRunning);
			}

			timeStep.Step();
		}

		if (entityEnabled)
		{
			/* Create new entities every single frame */
			Entity testEntity("Birb", Rect(rand.RandomInt(0, 64), rand.RandomInt(0, 64), 64, 64), texture.sdlTexture());

			testEntity.progressBarComponent = EntityComponent::ProgressBar(2, &Colors::White, &Colors::White, &Colors::Black);
			testEntity.progressBarComponent.value = rand.RandomFloat(0, 1);
			testEntity.progressBarComponent.minValue = 0;
			testEntity.progressBarComponent.maxValue = 1;

			testEntity.textComponent = EntityComponent::Text("Some text", &font, &Colors::Red);
			testEntity.clickComponent = EntityComponent::Click();
			testEntity.animationComponent = EntityComponent::Animation(Vector2Int(16, 16), 4, 10);

			scene.AddObject(&testEntity);
		}

		frameCounter++;

		/* Stop the test when [maxtime] seconds has elapsed */
		if (timer.ElapsedSeconds() > maxtime)
			ApplicationRunning = false;

		window.Clear();
		/* Start of rendering */
		
		scene.Render();

		/* End of rendering */
		window.Display();

		scene.Clear();

		timeStep.End();
	}

	Debug::Log("Test lasted [" + std::to_string(frameCounter) + "] frames");
	return 0;
}
