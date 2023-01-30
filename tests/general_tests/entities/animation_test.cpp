#include "doctest.h"
#include "Birb2D.hpp"

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Empty animation entity")
	{
		Entity::Animation animation;
		CHECK(animation.spriteSize == Vector2Int(16, 16));
		CHECK(animation.frameCount == 0);
		CHECK_FALSE(animation.animationQueued);
		CHECK(animation.frameIndex == 0);
		CHECK(animation.fps == 24);
		CHECK_FALSE(animation.loop);
		CHECK(animation.active);
		CHECK(animation.rect == Rect(0, 0, 0, 0));

		CHECK_FALSE(animation.ErrorFuseStatus());
	}

	TEST_CASE("Copy constructing an animation")
	{
		Entity::Animation animation;
		animation.spriteSize = Vector2Int(1, 1);
		animation.frameCount = 1;
		animation.animationQueued = true;
		animation.frameIndex = 1;
		animation.fps = 1;
		animation.loop = true;
		animation.active = false;
		animation.rect = Rect(1, 1, 1, 1);
		animation.parallax_multiplier = 4.1f;

		animation = Entity::Animation(Global::Placeholder::empty_texture, Vector2Int(3, 3), 5, 12, false);

		CHECK(animation.spriteSize == Vector2Int(3, 3));
		CHECK(animation.frameCount == 5);
		CHECK_FALSE(animation.animationQueued);
		CHECK(animation.frameIndex == 0);
		CHECK(animation.fps == 12);
		CHECK_FALSE(animation.loop);
		CHECK(animation.active);
		CHECK(animation.rect == Rect(0, 0, 0, 0));
		CHECK(animation.parallax_multiplier == 1.0f);

		CHECK_FALSE(animation.ErrorFuseStatus());
	}

	TEST_CASE("Late construct an animation entity")
	{
		Entity::Animation animation;
		animation.Construct(Global::Placeholder::empty_texture, Vector2Int(4, 4), 16, 10);

		CHECK_FALSE(animation.ErrorFuseStatus());
		CHECK(animation.sprite == Global::Placeholder::empty_texture);
		CHECK(animation.spriteSize == Vector2Int(4, 4));
		CHECK(animation.frameCount == 16);
		CHECK(animation.fps == 10);
		CHECK_FALSE(animation.animationQueued);
		CHECK(animation.frameIndex == 0);
		CHECK_FALSE(animation.loop);
		CHECK(animation.rect == Rect(0, 0, 0, 0));
	}

	TEST_CASE("Rendering: Animation entity")
	{
		Window window("Animation entity", Vector2Int(300, 300), 60, false);

		Texture texture("birb2d_res/loading.png");

		/* Make sure that the texture was loaded properly even though
		 * this test isn't about textures */
		CHECK(texture.isLoaded());
		CHECK_FALSE(texture.ErrorFuseStatus());

		Entity::Animation animation(texture, Vector2Int(3, 3), 15, 24, true);
		animation.sprite = texture;
		animation.rect = Rect(100, 100, 100, 100);

		Scene scene;
		scene.AddObject(&animation);

		/* Run a small rendering loop for 1 second */
		Timer timer;
		timer.Start();
		animation.StartAnimation();
		while (timer.ElapsedSeconds() < 1.0f)
		{
			window.Clear();
			scene.Render();
			window.Display();
			SDL_Delay(1 / window.refresh_rate);
		}

		CHECK_FALSE(animation.ErrorFuseStatus());
	}
}
