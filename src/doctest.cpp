#ifndef DOCTEST_CONFIG_DISABLE
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#else
#include <stdio.h>
int main(int argc, char** argv)
{
	printf("No tests have been built\n");
	return 0;
}
#endif

#include "doctest.h"
#include "Entity.hpp"
#include "Math.hpp"
#include "Values.hpp"
#include "Logger.hpp"
#include "Renderwindow.hpp"

TEST_CASE("Window and rendering functions")
{
	Birb::Window window("Title", Birb::Vector2int(1280, 720), 60, false);
	SDL_Texture* texture 	= Birb::Resources::LoadTexture("/home/toasterbirb/git/birb2d/res/textures/birb.png");
	TTF_Font* font 			= Birb::Resources::LoadFont("/home/toasterbirb/git/birb2d/res/fonts/freefont/FreeMonoBold.ttf", 32);
	Birb::Entity testEntity("Test entity", Birb::Vector2int(10, 10), texture);
	Birb::Entity secondEntityWithSameTexture("Second entity with the same texture", Birb::Rect(200, 400, 128 * 2, 72 * 2), texture);
	Birb::Entity rotatedEntity("Rotated entity with custom localscale", Birb::Rect(300, 100, 128, 72), texture);
	rotatedEntity.angle = 45;
	rotatedEntity.localScale = Birb::Vector2f(3.5, 2);
	Birb::Entity entityWithNegativeSize("Entity with negative size", Birb::Rect(300, 100, -128, 72), texture);


	Birb::Entity textEntity("Text entity", Birb::Vector2int(50, 250), Birb::EntityComponent::Text("Hello World", font, &Birb::Colors::Red));
	Birb::Entity textEntityWithBackground("Text entity with background color", Birb::Vector2int(50, 300), Birb::EntityComponent::Text("Hello World", font, &Birb::Colors::Red, &Birb::Colors::White));

	CHECK(window.win_title == "Title");
	CHECK(window.window_dimensions.x == 1280);
	CHECK(window.window_dimensions.y == 720);
	CHECK(window.refresh_rate == 60);
	CHECK(window.win 		!= NULL);
	CHECK(window.renderer 	!= NULL);
	CHECK(texture 	!= nullptr);
	CHECK(font 		!= nullptr);

	CHECK_NOTHROW(window.Clear());
	CHECK(Birb::Render::DrawEntity(testEntity));
	CHECK(Birb::Render::DrawEntity(secondEntityWithSameTexture));
	CHECK(Birb::Render::DrawEntity(rotatedEntity));
	CHECK_FALSE(Birb::Render::DrawEntity(entityWithNegativeSize));
	CHECK(Birb::Render::DrawEntity(textEntity));
	CHECK(Birb::Render::DrawEntity(textEntityWithBackground));

	CHECK_NOTHROW(Birb::Render::DrawCircle(Birb::Colors::White, Birb::Vector2int(400, 400), 50));
	CHECK_NOTHROW(Birb::Render::DrawLine(Birb::Colors::Red, Birb::Vector2int(450, 600), Birb::Vector2int(400, 200)));
	CHECK_NOTHROW(Birb::Render::DrawRect(Birb::Colors::Green, Birb::Rect(500, 500, 500, 20)));

	CHECK_NOTHROW(window.Display());
	SDL_Delay(1000);

	/* Try changing text */
	textEntity.SetText("Changed text :D");
	textEntity.SetColor(&Birb::Colors::Green);
	CHECK(textEntity.textComponent.text == "Changed text :D");
	CHECK(textEntity.textComponent.color == &Birb::Colors::Green);
	CHECK_NOTHROW(window.Clear());

	CHECK(Birb::Render::DrawEntity(testEntity));
	CHECK(Birb::Render::DrawEntity(secondEntityWithSameTexture));
	CHECK(Birb::Render::DrawEntity(rotatedEntity));
	CHECK_FALSE(Birb::Render::DrawEntity(entityWithNegativeSize));
	CHECK(Birb::Render::DrawEntity(textEntity));
	CHECK(Birb::Render::DrawEntity(textEntityWithBackground));

	CHECK_NOTHROW(Birb::Render::DrawCircle(Birb::Colors::White, Birb::Vector2int(400, 400), 50));
	CHECK_NOTHROW(Birb::Render::DrawLine(Birb::Colors::Red, Birb::Vector2int(450, 600), Birb::Vector2int(400, 200)));
	CHECK_NOTHROW(Birb::Render::DrawRect(Birb::Colors::Green, Birb::Rect(500, 500, 500, 20)));

	CHECK_NOTHROW(window.Display());
	SDL_Delay(1000);

	SDL_Texture* animationSprite = Birb::Resources::LoadTexture("./res/textures/birb_animation.png");
	Birb::Entity animationBirb(
			"Animated birb",
			Birb::Vector2int(100, 100),
			animationSprite,
			Birb::EntityComponent::Animation(
				Birb::Vector2int(64, 64),
				16,
				8,
				true));
	animationBirb.localScale = Birb::Vector2f(3, 3);
	animationBirb.animationComponent.StartAnimation();

	/* Progres bar */
	Birb::Entity progressBarEntity("Progress bar");
	progressBarEntity.rect = Birb::Rect(100, 300, 200, 25);
	progressBarEntity.progressBarComponent = Birb::EntityComponent::ProgressBar(2, &Birb::Colors::White, &Birb::Colors::DarkGray, &Birb::Colors::Green);

	/* Keep rendering for about 2 seoncds with a timer */
	Birb::Timer timer;
	timer.Start();
	
	bool animationSuccessful;
	bool progressBarSuccessful;
	while (timer.ElapsedSeconds() < 2)
	{
		window.Clear();
		animationSuccessful 	= Birb::Render::DrawEntity(animationBirb);
		
		progressBarEntity.progressBarComponent.value = timer.ElapsedSeconds() / 2.0;
		progressBarSuccessful 	= Birb::Render::DrawEntity(progressBarEntity);
		window.Display();
		SDL_Delay(16); /* Cap to around 60 fps, lets not waste CPU cycles... */
	}
	CHECK(animationSuccessful 	== true);
	CHECK(progressBarSuccessful == true);

	CHECK_NOTHROW(window.Cleanup());

	SDL_Quit();
}
