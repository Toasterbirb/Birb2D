#include "doctest.h"
#include "Birb2D.hpp"

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Text rendering")
	{
		TTF_Init();

		{
			Window window("Title", Vector2Int(1280, 720), 60, false);
			Font font("fonts/freefont/FreeMonoBold.ttf", 32);

			Scene testScene;
			testScene.Activate();

			Entity greenText("Normal green text", Vector2Int(50, 50), EntityComponent::Text("", &font, &Colors::Green));
			CHECK(greenText.textComponent.color == &Colors::Green);
			CHECK(greenText.textComponent.text == "");
			CHECK(greenText.SetText("Normal green text"));
			CHECK(greenText.textComponent.text == "Normal green text");

			Entity multilineWhiteText("Multiline white text", Vector2Int(50, 120), EntityComponent::Text("", &font, &Colors::White));
			CHECK(multilineWhiteText.textComponent.color == &Colors::White);
			CHECK(multilineWhiteText.textComponent.text == "");
			CHECK(multilineWhiteText.SetText("1. First line\n2. Second line\n3. Third line"));
			CHECK(multilineWhiteText.textComponent.text == "1. First line\n2. Second line\n3. Third line");
			testScene.AddObject(&multilineWhiteText);

			Entity textWithBackground("Text with background", Vector2Int(50, 250), EntityComponent::Text("", &font, &Colors::LightGray, &Colors::DarkGray));
			CHECK(textWithBackground.textComponent.color == &Colors::LightGray);
			CHECK(textWithBackground.textComponent.bgColor == &Colors::DarkGray);
			CHECK(textWithBackground.textComponent.text == "");
			CHECK(textWithBackground.SetText("Text with a background color"));
			CHECK(textWithBackground.textComponent.text == "Text with a background color");
			testScene.AddObject(&textWithBackground);

			Entity changingText("Changing text", Vector2Int(50, 300), EntityComponent::Text("Frame: 0", &font, &Colors::DarkGray, &Colors::LightGray));
			CHECK(changingText.textComponent.color == &Colors::DarkGray);
			CHECK(changingText.textComponent.bgColor == &Colors::LightGray);
			testScene.AddObject(&changingText);

			/* Render 24 frames to test changing text. This test should last about 1,5 seconds */
			const int frame_count = 24;

			for (int i = 0; i < frame_count; ++i)
			{
				/* Update the changing text */
				CHECK(changingText.SetText("Frame: " + std::to_string(i)));

				window.Clear();

				/* Draw the "normal green text" manually */
				CHECK(Render::DrawEntity(greenText));

				testScene.Render();
				window.Display();
				SDL_Delay(62);
			}
		}

		TTF_Quit();
	}
}
