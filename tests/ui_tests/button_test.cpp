#include "doctest.h"
#include "Birb2D.hpp"

using namespace Birb;

namespace BirbTest
{
	static bool success = false;

	static void ButtonClick()
	{
		Debug::Log("Button click registered!");
		success = true;
	}

	static void ButtonHover()
	{
		Debug::Log("Button on-hover registered!");
		success = true;
	}

	TEST_CASE("Input: Button click")
	{
		TTF_Init();

		{
			success = false;

			Vector2Int button_dimensions(200, 200);

			/* Setup a simple window and a game loop */
			Window window("UI Test", Vector2Int(1280, 720), 75, false);
			TimeStep timeStep;
			timeStep.Init(&window);

			UI ui;
			Entity::Button button("Button", Rect(window.dimensions.x / 2.2 - button_dimensions.x / 2.0, window.dimensions.y / 2.0 - button_dimensions.y / 2.0, button_dimensions.x, button_dimensions.y));
			button.onClick = ButtonClick;
			CHECK(button.active);

			button.rect.color = Colors::Red;
			ui.AddButton(&button);
			CHECK(ui.Buttons[0] == &button);

			double timeout = 10.0;
			Font font("fonts/freefont/FreeMonoBold.ttf", 24);
			Entity::Text instruction_text("Instruction text", Vector2Int(100, 100), "*Click* the red square!\n\nIf nothing happens, there's a bug to fix.\nThis test will timeout in " + std::to_string((int)timeout) + " seconds", &font, Colors::White);

			Scene testScene;
			testScene.AddObject(&button);
			testScene.AddObject(&instruction_text);

			Timer timer;
			timer.Start();

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

						ui.PollButtons(window);
					}

					timeStep.Step();
				}

				if (button.isPressed)
					button.rect.color.ChangeIntensity(10);

				if (success)
					ApplicationRunning = false;

				window.Clear();
				/* Handle rendering */

				testScene.Render();

				/* End of rendering */
				window.Display();

				timeStep.End();

				if (timer.ElapsedSeconds() > timeout)
					ApplicationRunning = false;
			}

			CHECK(success);
			CHECK_FALSE(button.ErrorFuseStatus());
		}

		TTF_Quit();
	}

	TEST_CASE("Input: Button hover")
	{
		TTF_Init();

		{
			success = false;

			Vector2Int button_dimensions(200, 100);

			/* Setup a simple window and a game loop */
			Window window("UI Test", Vector2Int(1280, 720), 75, false);
			TimeStep timeStep;
			timeStep.Init(&window);

			UI ui;
			Entity::Button button("Button", Rect(window.dimensions.x / 1.5 - button_dimensions.x / 2.0, window.dimensions.y / 2.0 - button_dimensions.y / 2.0, button_dimensions.x, button_dimensions.y));
			button.onHover = ButtonHover;
			CHECK(button.active);

			button.rect.color = Colors::Green;
			ui.AddButton(&button);
			CHECK(ui.Buttons[0] == &button);

			double timeout = 10.0;
			Font font("fonts/freefont/FreeMonoBold.ttf", 24);
			Entity::Text instruction_text("Instruction text", Vector2Int(100, 100), "*Hover* your cursor over the green square!\n\nIf nothing happens, there's a bug to fix.\nThis test will timeout in " + std::to_string((int)timeout) + " seconds", &font, Colors::White);

			Scene testScene;
			testScene.AddObject(&button);
			testScene.AddObject(&instruction_text);

			Timer timer;
			timer.Start();

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

						ui.PollButtons(window);
					}

					timeStep.Step();
				}

				if (success)
					ApplicationRunning = false;

				window.Clear();
				/* Handle rendering */

				testScene.Render();

				/* End of rendering */
				window.Display();

				timeStep.End();

				if (timer.ElapsedSeconds() > timeout)
					ApplicationRunning = false;
			}

			CHECK(success);
			CHECK_FALSE(button.ErrorFuseStatus());
		}

		TTF_Quit();
	}

	bool ButtonA_clicked = false;
	void ButtonAClick()
	{
		ButtonA_clicked = true;
		Debug::Log("Button A was clicked");
	}

	bool ButtonB_clicked = false;
	void ButtonBClick()
	{
		ButtonB_clicked = true;
		Debug::Log("Button B was clicked");
	}

	TEST_CASE("Input: Overlapping button click")
	{
		TTF_Init();

		{
			ButtonA_clicked = false;
			ButtonB_clicked = false;

			Vector2Int button_dimensions(200, 200);

			/* Setup a simple window and a game loop */
			Window window("UI Test", Vector2Int(1280, 720), 75, false);
			TimeStep timeStep;
			timeStep.Init(&window);

			UI ui;

			/* Button A */
			Entity::Button buttonA("Button A", Rect(window.dimensions.x / 2.2 - button_dimensions.x / 2.0, window.dimensions.y / 2.0 - button_dimensions.y / 2.0, button_dimensions.x, button_dimensions.y));
			buttonA.onClick = ButtonAClick;
			CHECK(buttonA.active);

			buttonA.rect.color = Colors::Red;
			buttonA.renderingPriority = 3;

			/* Button B */
			Entity::Button buttonB("Button B", Rect(window.dimensions.x / 2.2 - button_dimensions.x / 2.0, window.dimensions.y / 2.0 - button_dimensions.y / 2.0, button_dimensions.x, button_dimensions.y));
			buttonB.onClick = ButtonBClick;
			CHECK(buttonB.active);

			buttonB.rect.color = Colors::Blue;
			buttonB.renderingPriority = 2;

			ui.AddButton(&buttonB);
			ui.AddButton(&buttonA);
			CHECK(ui.Buttons[0] == &buttonA);
			CHECK(ui.Buttons[1] == &buttonB);

			double timeout = 10.0;
			Font font("fonts/freefont/FreeMonoBold.ttf", 24);
			Entity::Text instruction_text("Instruction text", Vector2Int(100, 100), "*Click* the red square!\nThere are two buttons on top of eachother and only one of them should activate.\n\nIf nothing happens, there's a bug to fix.\nThis test will timeout in " + std::to_string((int)timeout) + " seconds", &font, Colors::White);

			Scene testScene;
			testScene.AddObject(&buttonB);
			testScene.AddObject(&buttonA);
			testScene.AddObject(&instruction_text);
			CHECK(testScene.GetObjects()[0] == &instruction_text);
			CHECK(testScene.GetObjects()[1] == &buttonB);
			CHECK(testScene.GetObjects()[2] == &buttonA);

			Timer timer;
			timer.Start();

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

						ui.PollButtons(window);
					}

					timeStep.Step();
				}

				if (ButtonA_clicked || ButtonB_clicked)
					ApplicationRunning = false;

				window.Clear();
				/* Handle rendering */

				testScene.Render();

				/* End of rendering */
				window.Display();

				timeStep.End();

				if (timer.ElapsedSeconds() > timeout)
					ApplicationRunning = false;
			}

			CHECK(ButtonA_clicked);
			CHECK_FALSE(ButtonB_clicked);

			CHECK_FALSE(buttonA.ErrorFuseStatus());
			CHECK_FALSE(buttonB.ErrorFuseStatus());
		}

		TTF_Quit();
	}
}
