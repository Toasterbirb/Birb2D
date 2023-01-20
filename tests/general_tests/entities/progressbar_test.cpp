#include "doctest.h"
#include "Birb2D.hpp"

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Empty progressbar")
	{
		Entity::ProgressBar progress;
		CHECK(progress.active);
		CHECK(progress.backgroundColor == Colors::Black);
		CHECK(progress.borderColor == Colors::White);
		CHECK(progress.fillColor == Colors::White);
		CHECK(progress.borderWidth == 1);
		CHECK(progress.minValue == 0);
		CHECK(progress.maxValue == 1);
		CHECK(progress.value == 0);
		CHECK(progress.rect == Rect(0, 0, 0, 0));
	}

	TEST_CASE("Secondary progressbar constructor")
	{
		Entity::ProgressBar progress(3, Colors::Nord::PolarNight::nord3, Colors::Nord::PolarNight::nord0, Colors::Nord::Aurora::nord15, 0, 200, 25);
		CHECK(progress.minValue == 0);
		CHECK(progress.maxValue == 200);
		CHECK(progress.value == 25);
	}

	TEST_CASE("Copy constructing a progressbar entity")
	{
		Entity::ProgressBar progress;
		progress.name = "ASDF";
		progress.active = false;
		progress.backgroundColor = Colors::Black;
		progress.parallax_multiplier = 10.0f;
		progress.world_space = false;

		progress = Entity::ProgressBar(3, Colors::Nord::PolarNight::nord3, Colors::Nord::PolarNight::nord0, Colors::Nord::Aurora::nord12);

		CHECK(progress.borderWidth == 3);
		CHECK(progress.borderColor == Colors::Nord::PolarNight::nord3);
		CHECK(progress.backgroundColor == Colors::Nord::PolarNight::nord0);
		CHECK(progress.fillColor == Colors::Nord::Aurora::nord12);
		CHECK(progress.name == "Default Entity");
		CHECK(progress.active);
		CHECK(progress.parallax_multiplier == 1.0f);
		CHECK(progress.world_space);
	}

	TEST_CASE("Rendering: Progressbar drawing")
	{
		Entity::ProgressBar progress_A(3, Colors::Nord::PolarNight::nord3, Colors::Nord::PolarNight::nord0, Colors::Nord::Aurora::nord12);
		progress_A.rect = Rect(32, 32, 576, 64);
		CHECK(progress_A.active);

		Entity::ProgressBar progress_B(3, Colors::Nord::PolarNight::nord3, Colors::Nord::PolarNight::nord0, Colors::Nord::Aurora::nord15, 0, 200, 0);
		progress_B.rect = Rect(32, progress_A.rect.y + progress_A.rect.h + 32, 576, 64);
		CHECK(progress_B.active);

		SceneObject* objs[2] = { &progress_A, &progress_B };

		Scene scene;
		scene.AddObject(objs, 2);

		Window window("Progressbar rendering test", Vector2Int(640, static_cast<int>(progress_B.rect.y + progress_B.rect.h + 32)), 60, false);

		/* Draw for about half a second */
		for (int i = 0; i < window.refresh_rate / 2; ++i)
		{
			window.Clear();
			scene.Render();
			window.Display();

			progress_A.value = (static_cast<float>(i) / (window.refresh_rate / 2.0f)) * progress_A.maxValue;
			progress_B.value = (static_cast<float>(i) / (window.refresh_rate / 2.0f)) * progress_B.maxValue;

			SDL_Delay(17);
		}
	}
}
