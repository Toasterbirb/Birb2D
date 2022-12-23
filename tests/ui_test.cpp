#include "doctest.h"
#include "Birb2D.hpp"

namespace Birb
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
		success = false;

		Vector2Int button_dimensions(200, 200);

		/* Setup a simple window and a game loop */
		Window window("UI Test", Vector2Int(1280, 720), 75, false);
		TimeStep timeStep;
		timeStep.Init(&window);

		UI ui;
		Entity button("Button", Rect(window.dimensions.x / 2.2 - button_dimensions.x / 2.0, window.dimensions.y / 2.0 - button_dimensions.y / 2.0, button_dimensions.x, button_dimensions.y));
		button.clickComponent.onClick = ButtonClick;
		CHECK(button.clickComponent.active);

		button.rect.color = Colors::Red;
		ui.AddButton(&button);
		CHECK(ui.Buttons[0] == &button);

		double timeout = 10.0;
		Font font("fonts/freefont/FreeMonoBold.ttf", 24);
		Entity instruction_text("Instruction text", Vector2Int(100, 100), EntityComponent::Text("*Click* the red square!\n\nIf nothing happens, there's a bug to fix.\nThis test will timeout in " + std::to_string((int)timeout) + " seconds", &font, &Colors::White));

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

			if (button.clickComponent.isPressed)
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

		font.Free();
	}

	TEST_CASE("Input: Button hover")
	{
		success = false;

		Vector2Int button_dimensions(200, 100);

		/* Setup a simple window and a game loop */
		Window window("UI Test", Vector2Int(1280, 720), 75, false);
		TimeStep timeStep;
		timeStep.Init(&window);

		UI ui;
		Entity button("Button", Rect(window.dimensions.x / 1.5 - button_dimensions.x / 2.0, window.dimensions.y / 2.0 - button_dimensions.y / 2.0, button_dimensions.x, button_dimensions.y));
		button.clickComponent.onHover = ButtonHover;
		CHECK(button.clickComponent.active);

		button.rect.color = Colors::Green;
		ui.AddButton(&button);
		CHECK(ui.Buttons[0] == &button);

		double timeout = 10.0;
		Font font("fonts/freefont/FreeMonoBold.ttf", 24);
		Entity instruction_text("Instruction text", Vector2Int(100, 100), EntityComponent::Text("*Hover* your cursor over the green square!\n\nIf nothing happens, there's a bug to fix.\nThis test will timeout in " + std::to_string((int)timeout) + " seconds", &font, &Colors::White));

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

		font.Free();
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
		ButtonA_clicked = false;
		ButtonB_clicked = false;

		Vector2Int button_dimensions(200, 200);

		/* Setup a simple window and a game loop */
		Window window("UI Test", Vector2Int(1280, 720), 75, false);
		TimeStep timeStep;
		timeStep.Init(&window);

		UI ui;

		/* Button A */
		Entity buttonA("Button A", Rect(window.dimensions.x / 2.2 - button_dimensions.x / 2.0, window.dimensions.y / 2.0 - button_dimensions.y / 2.0, button_dimensions.x, button_dimensions.y));
		buttonA.clickComponent.onClick = ButtonAClick;
		CHECK(buttonA.clickComponent.active);

		buttonA.rect.color = Colors::Red;
		buttonA.renderingPriority = 3;

		/* Button B */
		Entity buttonB("Button B", Rect(window.dimensions.x / 2.2 - button_dimensions.x / 2.0, window.dimensions.y / 2.0 - button_dimensions.y / 2.0, button_dimensions.x, button_dimensions.y));
		buttonB.clickComponent.onClick = ButtonBClick;
		CHECK(buttonB.clickComponent.active);

		buttonB.rect.color = Colors::Blue;
		buttonB.renderingPriority = 2;

		ui.AddButton(&buttonB);
		ui.AddButton(&buttonA);
		CHECK(ui.Buttons[0] == &buttonA);
		CHECK(ui.Buttons[1] == &buttonB);

		double timeout = 10.0;
		Font font("fonts/freefont/FreeMonoBold.ttf", 24);
		Entity instruction_text("Instruction text", Vector2Int(100, 100), EntityComponent::Text("*Click* the red square!\nThere are two buttons on top of eachother and only one of them should activate.\n\nIf nothing happens, there's a bug to fix.\nThis test will timeout in " + std::to_string((int)timeout) + " seconds", &font, &Colors::White));

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

		font.Free();
	}
}
