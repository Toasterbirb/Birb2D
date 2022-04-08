#include <memory>
#include "doctest.h"
#include "Renderwindow.hpp"
#include "Values.hpp"
#include "Scene.hpp"
#include "Timestep.hpp"
#include "Texture.hpp"

namespace Birb
{
	TEST_CASE("Rendering: Renderwindow")
	{
		Window window("Birb2D tests", Vector2int(1280, 720), 75, false);

		CHECK(window.refresh_rate == 75);
		CHECK(window.dimensions == Vector2int(1280, 720));
		CHECK(window.win_title == "Birb2D tests");
		CHECK(window.original_window_dimensions == Vector2int(1280, 720));

		CHECK(Global::RenderVars::Renderer == window.renderer);
		CHECK(Global::RenderVars::RefreshRate == 75);
		CHECK(window.win == Global::RenderVars::MainWindow);
		CHECK(Global::RenderVars::BackgroundColor == Colors::Black);
	}

	void RenderLoop(const Scene& scene, Window window)
	{
		TimeStep timeStep;
		timeStep.Init(&window);
		Timer testTimer;
		testTimer.Start();

		CHECK(scene.isActive());

		bool ApplicationRunning = true;
		while (ApplicationRunning)
		{
			if (testTimer.ElapsedSeconds() > 0.5)
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

			scene.Render();

			/** End of rendering **/
			window.Display();
			timeStep.End();
		}
	}

	TEST_CASE("Rendering: General")
	{
		Window window("Birb2D tests", Vector2int(1280, 720), 75, false);
		ApplicationInfo appInfo("Birb2D_tests");
		Scene scene;
		scene.Activate();

		/* Place to store stuff in subcases */
		std::vector<Entity> entities;
		std::vector<Circle> circles;

		SUBCASE("Sprites / Textures in a scene")
		{
			const int ENTITY_COUNT = 5;
			Texture birbSprite(appInfo.ResLocation + "/textures/birb.png");

			/* Create the entities */
			for (int i = 0; i < ENTITY_COUNT; i++)
			{
				Entity testEntity("Test entity", Vector2int(i * 70, 10), birbSprite.sdlTexture());
				entities.push_back(testEntity);
			}

			/* Add the entities to the scene */
			for (int i = 0; i < entities.size(); i++)
				scene.AddObject(&entities[i]);

			CHECK(scene.ObjectCount() == ENTITY_COUNT);

			RenderLoop(scene, window);

			/* Free stuff */
			birbSprite.Destroy();
		}

		SUBCASE("Scenes inside of other scenes")
		{
			/* Create a child scene */
			Scene childScene;

			/* Create two rects for the background */
			Rect rectA(Rect(0, 0, 640, 720, Colors::LightGray));
			Rect rectB(Rect(640, 0, 640, 720, Colors::DarkGray));
			Rect rectC(Rect(320, 180, 640, 360, Colors::Red));

			scene.AddObject(&rectA);
			scene.AddObject(&rectB);

			/* Create a rect to put into the child scene */
			rectC.renderingPriority = 1;
			childScene.AddObject(&rectC);

			/* Add the childscene as a SceneObject into the main scene */
			childScene.renderingPriority = 1;
			scene.AddObject(&childScene);

			CHECK(scene.ObjectCount() == 3);
			CHECK(childScene.ObjectCount() == 1);

			RenderLoop(scene, window);
		}

	}
}
