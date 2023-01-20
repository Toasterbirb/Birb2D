#include "doctest.h"
#include "Birb2D.hpp"

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Empty image entity")
	{
		Entity::Image image;
		CHECK_FALSE(image.ErrorFuseStatus());
		CHECK(image.name == "Default Entity");
		CHECK(image.active);
		CHECK(image.angle == 0);
		CHECK(image.sprite == Global::Placeholder::empty_texture);
		CHECK(image.rect == Rect(0, 0, 0, 0));
	}

	TEST_CASE("Construct an image entity via copy")
	{
		Entity::Image image;
		image.active 				= false;
		image.parallax_multiplier 	= 4.0f;
		image.world_space 			= false;
		image.angle 				= 10;
		image.rect 					= Rect(1, 1, 1, 1);
		image.renderingPriority 	= 3;

		image = Entity::Image("Name", Vector2Int(10, 20), Global::Placeholder::empty_texture);
		CHECK(image.name == "Name");
		CHECK(image.active);
		CHECK(image.parallax_multiplier == 1.0f);
		CHECK(image.world_space);
		CHECK(image.angle == 0);
		CHECK(image.rect == Rect(10, 20, 0, 0));
		CHECK(image.renderingPriority == 0);
		CHECK_FALSE(image.ErrorFuseStatus());
		CHECK(image.sprite == Global::Placeholder::empty_texture);
	}

	TEST_CASE("Rendering: Draw image entities")
	{
		Window window("Image entity rendering", Vector2Int(750, 446), 60, false);

		/* Load a texture */
		Texture texture("birb2d_res/logo.png");

		/* Create some entities with different constructors */
		Entity::Image image_A(texture, Rect(32, 32, 130, 110));
		CHECK(image_A.sprite == texture);
		CHECK(image_A.rect == Rect(32, 32, 130, 110));

		Entity::Image image_B("Image", Rect(image_A.rect.x + image_A.rect.w + 64, 32, 130, 110), texture);
		CHECK(image_B.name == "Image");
		CHECK(image_B.rect == Rect(image_A.rect.x + image_A.rect.w + 64, 32, 130, 110));
		CHECK(image_B.sprite == texture);

		Entity::Image image_C("Image 2", Vector2Int(static_cast<int>(image_B.rect.x + image_A.rect.w + 64), 32), texture);
		image_C.rect.w = 130;
		image_C.rect.h = 110;
		CHECK(image_C.name == "Image 2");
		CHECK(image_C.rect == Rect(image_B.rect.x + image_A.rect.w + 64, 32, 130, 110));
		CHECK(image_C.sprite == texture);


		/* Add the images into a scene */
		Scene scene;
		SceneObject* objs[] = { &image_A, &image_B, &image_C };
		scene.AddObject(objs, 3);

		/* Render a few frames and rotate the last image while moving it down */
		for (int i = 0; i < 16; ++i)
		{
			window.Clear();
			scene.Render();
			window.Display();

			image_C.angle += 24;
			image_C.rect.y += 20;

			SDL_Delay(32);
		}

		/* Check fuses */
		CHECK_FALSE(image_A.ErrorFuseStatus());
		CHECK_FALSE(image_B.ErrorFuseStatus());
		CHECK_FALSE(image_C.ErrorFuseStatus());

		SDL_Delay(500);
	}
}
