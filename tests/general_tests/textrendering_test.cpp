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

			Entity::Text greenText;
			greenText.Construct("", Vector2Int(50, 50), &font, Colors::Green);

			CHECK(greenText.GetColor() == Colors::Green);
			CHECK(greenText.GetText() == "");
			CHECK(greenText.SetText("Normal green text"));
			CHECK(greenText.GetText() == "Normal green text");
			testScene.AddObject(&greenText);

			Entity::Text multilineWhiteText("Multiline white text", Vector2Int(50, 120), "", &font, Colors::Black);
			CHECK(multilineWhiteText.GetColor() == Colors::Black);

			multilineWhiteText.SetTextColor(Colors::White);

			CHECK(multilineWhiteText.GetColor() == Colors::White);
			CHECK(multilineWhiteText.GetText() == "");
			CHECK(multilineWhiteText.SetText("1. First line\n2. Second line\n3. Third line"));
			CHECK(multilineWhiteText.GetText() == "1. First line\n2. Second line\n3. Third line");
			CHECK(multilineWhiteText.sprite_dimensions() != Vector2Int(0, 0));
			testScene.AddObject(&multilineWhiteText);

			Entity::Text textWithBackground;
			CHECK(textWithBackground.GetText() == "");

			textWithBackground = Entity::Text("Text with background", Vector2Int(50, 250), "", &font, Colors::LightGray, Colors::DarkGray);
			CHECK(textWithBackground.GetColor() == Colors::LightGray);
			CHECK(textWithBackground.GetBgColor() == Colors::DarkGray);
			CHECK(textWithBackground.GetText() == "");
			CHECK(textWithBackground.SetText("Text with a background color"));
			CHECK(textWithBackground.GetText() == "Text with a background color");
			testScene.AddObject(&textWithBackground);

			Entity::Text changingText("Changing text", Vector2Int(50, 300), "Frame: 0", &font, Colors::DarkGray, Colors::LightGray);
			CHECK(changingText.GetColor() == Colors::DarkGray);
			CHECK(changingText.GetBgColor() == Colors::LightGray);
			testScene.AddObject(&changingText);

			/* Render 24 frames to test changing text. This test should last about 1,5 seconds */
			const int frame_count = 24;

			for (int i = 0; i < frame_count; ++i)
			{
				/* Update the changing text */
				CHECK(changingText.SetText("Frame: " + std::to_string(i)));

				window.Clear();

				testScene.Render();
				window.Display();
				SDL_Delay(62);
			}

			/* Check fuses */
			CHECK_FALSE(greenText.ErrorFuseStatus());
			CHECK_FALSE(multilineWhiteText.ErrorFuseStatus());
			CHECK_FALSE(textWithBackground.ErrorFuseStatus());
			CHECK_FALSE(changingText.ErrorFuseStatus());
		}

		TTF_Quit();
	}
}
