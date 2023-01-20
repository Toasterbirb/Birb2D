#include <memory>
#include "Entities/Image.hpp"
#include "Renderwindow.hpp"
#include "Scene.hpp"
#include "Texture.hpp"
#include "Timer.hpp"
#include "Timestep.hpp"
#include "Values.hpp"
#include "doctest.h"

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Rendering: Renderwindow")
	{
		Window window("Birb2D tests", Vector2Int(1280, 720), 75, false);

		CHECK(window.refresh_rate == 75);
		CHECK(window.dimensions == Vector2Int(1280, 720));
		CHECK(window.win_title == "Birb2D tests");
		CHECK(window.original_window_dimensions == Vector2Int(1280, 720));

		CHECK(Global::RenderVars::Renderer == window.renderer);
		CHECK(window.win == Global::RenderVars::MainWindow);

		CHECK(Global::RenderVars::RefreshRate == 75);
		CHECK(Global::RenderVars::BackgroundColor == Colors::Black);
	}

	void RenderLoop(const Scene& scene, Window& window)
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
		Window window("Birb2D tests", Vector2Int(1280, 720), 75, false);
		Scene scene;
		scene.Activate();

		/* Place to store stuff in subcases */
		std::vector<Entity::Image> entities;
		std::vector<Circle> circles;

		SUBCASE("Sprites / Textures in a scene")
		{
			Texture emptyTexture;
			CHECK(emptyTexture.isLoaded() == false);
			CHECK(emptyTexture.dimensions() == Vector2Int(0, 0));

			/* Now load the texture manually */
			CHECK(emptyTexture.LoadTexture("textures/birb.png"));
			CHECK(emptyTexture.isLoaded() == true);
			CHECK(emptyTexture.dimensions() == Vector2Int(64, 64));


			const int ENTITY_COUNT = 5;
			Texture birbSprite("textures/birb.png");

			CHECK(birbSprite.isLoaded() == true);
			CHECK(birbSprite.dimensions() == Vector2Int(64, 64));

			/* Create the entities */
			for (int i = 0; i < ENTITY_COUNT; i++)
			{
				Entity::Image testEntity("Test entity", Vector2Int(i * 70, 10), birbSprite);
				entities.push_back(testEntity);
			}

			/* Add the entities to the scene */
			for (size_t i = 0; i < entities.size(); i++)
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
