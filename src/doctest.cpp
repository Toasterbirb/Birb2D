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
#include "Circle.hpp"
#include "Entity.hpp"
#include "Font.hpp"
#include "Graphs.hpp"
#include "Math.hpp"
#include "Values.hpp"
#include "Logger.hpp"
#include "Utils.hpp"
#include "Scene.hpp"
#include "Polygon.hpp"
#include "Renderwindow.hpp"

TEST_CASE("Window and rendering functions")
{
	Birb::ApplicationInfo appInfo("Birb2D_tests");

	Birb::Window window("Title", Birb::Vector2int(1280, 720), 60, false);
	SDL_Texture* texture 	= Birb::Resources::LoadTexture(appInfo.ResLocation + "/textures/birb.png");
	Birb::Font font(appInfo.ResLocation + "/fonts/freefont/FreeMonoBold.ttf", 32);
	
	Birb::Scene testScene;

	Birb::Entity testEntity("Test entity", Birb::Vector2int(10, 10), texture);
	Birb::Entity secondEntityWithSameTexture("Second entity with the same texture", Birb::Rect(200, 400, 128 * 2, 72 * 2), texture);
	Birb::Entity rotatedEntity("Rotated entity with custom localscale", Birb::Rect(300, 100, 128, 72), texture);
	rotatedEntity.angle = 45;
	rotatedEntity.localScale = Birb::Vector2f(3.5, 2);
	Birb::Entity entityWithNegativeSize("Entity with negative size", Birb::Rect(300, 100, -128, 72), texture);

	Birb::Line line(Birb::Vector2f(0, 0), Birb::Vector2f(1280, 720));
	line.renderingPriority = -1;

	Birb::Line lineB({0, 720}, {1280, 0});

	Birb::Rect renderedRect(0, 0, 100, 100);
	renderedRect.renderingPriority = -5;

	Birb::Polygon polygon(
	{
		Birb::Vector2f(0, 200),
		Birb::Vector2f(200, 184),
		Birb::Vector2f(230, 110),
		Birb::Vector2f(0, 180)
	}, 0x81E176);

	Birb::Circle circle(32, {500, 650}, 0x32DDAA);

	/* Add entities etc. to the scene */
	testScene.AddObject(&testEntity);
	testScene.AddObject(&secondEntityWithSameTexture);
	testScene.AddObject(&rotatedEntity);
	testScene.AddObject(&line);
	testScene.AddObject(&renderedRect);
	testScene.AddObject(&polygon);
	testScene.AddObject(&circle);

	/* Graph */
	std::vector<double> values = {
		1.5, 12, 5.6, 2.7, 7, 6, 15
	};

	Birb::Widgets::Graph lineGraph(Birb::Widgets::GraphType::Line,
			values,
			Birb::Rect(800, 50, 260, 180));
	lineGraph.graphColor 		= Birb::Colors::Green;
	lineGraph.backgroundColor 	= Birb::Colors::Black;

	Birb::Widgets::Graph blockGraph(Birb::Widgets::GraphType::Block,
			values,
			Birb::Rect(800, 250, 260, 180));
	blockGraph.graphColor 		= Birb::Colors::Red;
	blockGraph.backgroundColor 	= Birb::Colors::Black;

	Birb::Widgets::Graph areaGraph(Birb::Widgets::GraphType::Area,
			values,
			Birb::Rect(800, 450, 260, 180));
	areaGraph.graphColor 		= Birb::Colors::Blue;
	areaGraph.backgroundColor 	= Birb::Colors::Black;
	testScene.AddObject(&areaGraph);

	

	Birb::Entity textEntity("Text entity", Birb::Vector2int(50, 250), Birb::EntityComponent::Text("Hello World", &font, &Birb::Colors::Red));
	Birb::Entity textEntityWithBackground("Text entity with background color", Birb::Vector2int(50, 300), Birb::EntityComponent::Text("Hello World", &font, &Birb::Colors::Red, &Birb::Colors::White));

	CHECK(window.win_title == "Title");
	CHECK(window.dimensions.x == 1280);
	CHECK(window.dimensions.y == 720);
	CHECK(window.refresh_rate == 60);
	CHECK(window.win 		!= NULL);
	CHECK(window.renderer 	!= NULL);
	CHECK(texture 	!= nullptr);
	CHECK(font.ttf() 		!= nullptr);

	CHECK_NOTHROW(window.Clear());
	{
		CHECK_NOTHROW(testScene.Render());
		CHECK_FALSE(Birb::Render::DrawEntity(entityWithNegativeSize));
		CHECK(Birb::Render::DrawEntity(textEntity));
		CHECK(Birb::Render::DrawEntity(textEntityWithBackground));

		CHECK(Birb::Render::DrawCircle(Birb::Colors::Blue, Birb::Vector2int(400, 400), 50));
		CHECK_NOTHROW(Birb::Render::DrawLine(Birb::Colors::Red, Birb::Vector2int(450, 600), Birb::Vector2int(400, 200)));
		CHECK_NOTHROW(Birb::Render::DrawRect(Birb::Colors::Green, Birb::Rect(500, 500, 200, 20)));

		/* Draw a polygon */
		Birb::Vector2int polyPoints[5] = {
			Birb::Vector2int(100, 59),
			Birb::Vector2int(150, 34),
			Birb::Vector2int(170, 99),
			Birb::Vector2int(87, 24),
			Birb::Vector2int(53, 10),
		};
		CHECK(Birb::Render::DrawPolygon(Birb::Colors::White, polyPoints, 5));

		/* Draw the graphs */
		lineGraph.Render();
		blockGraph.Render();

		/* Draw a thick line over everything */
		Birb::Render::DrawLine(lineB, 2);

	}
	CHECK_NOTHROW(window.Display());
	SDL_Delay(1000);

	/* Try changing text */
	textEntity.SetText("The birbs disappeared");
	textEntity.SetColor(&Birb::Colors::Green);
	CHECK(textEntity.textComponent.text == "The birbs disappeared");
	CHECK(textEntity.textComponent.color == &Birb::Colors::Green);

	/* Toggle the test scene */
	testScene.Toggle();

	CHECK_NOTHROW(window.Clear());
	{
		/* Draw a polygon */
		std::vector<Birb::Vector2int> polyPoints2 = {
			Birb::Vector2int(10, 5),
			Birb::Vector2int(150, 34),
			Birb::Vector2int(170, 99),
			Birb::Vector2int(87, 24),
			Birb::Vector2int(53, 10),
		};
		CHECK(Birb::Render::DrawPolygon(Birb::Colors::White, polyPoints2));

		testScene.Render();
		CHECK_FALSE(Birb::Render::DrawEntity(entityWithNegativeSize));
		CHECK(Birb::Render::DrawEntity(textEntity));
		CHECK(Birb::Render::DrawEntity(textEntityWithBackground));

		CHECK(Birb::Render::DrawCircle(Birb::Colors::White, Birb::Vector2int(400, 400), 50));
		CHECK_NOTHROW(Birb::Render::DrawLine(Birb::Colors::Red, Birb::Vector2int(450, 600), Birb::Vector2int(400, 200)));
		CHECK_NOTHROW(Birb::Render::DrawRect(Birb::Colors::Green, Birb::Rect(500, 500, 200, 20)));

		/* Draw the graph */
		lineGraph.Render();
		blockGraph.Render();

		/* Draw a thick line over everything */
		Birb::Render::DrawLine(lineB, 4);
	}

	CHECK_NOTHROW(window.Display());
	SDL_Delay(1000);

	SDL_Texture* animationSprite = Birb::Resources::LoadTexture(appInfo.ResLocation + "/textures/birb_animation.png");
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

	/* Frametime graph */
	std::vector<double> frameTimes;
	Birb::Widgets::Graph frameTimeGraph(Birb::Widgets::GraphType::Line, frameTimes, Birb::Rect(100, 400, 500, 150));

	/* Keep rendering for about 2 seoncds with a timer */
	Birb::Timer timer;
	timer.Start();
	
	bool animationSuccessful;
	bool progressBarSuccessful;
	double currentTime = Birb::utils::hireTimeInSeconds();
	while (timer.ElapsedSeconds() < 2)
	{
		SDL_Delay(16); /* Cap to around 60 fps, lets not waste CPU cycles... */
		window.Clear();
		animationSuccessful 	= Birb::Render::DrawEntity(animationBirb);
		
		progressBarEntity.progressBarComponent.value = timer.ElapsedSeconds() / 2.0;
		progressBarSuccessful 	= Birb::Render::DrawEntity(progressBarEntity);

		double newTime = Birb::utils::hireTimeInSeconds();
		frameTimeGraph.values.push_back(newTime - currentTime);
		currentTime = newTime;
		frameTimeGraph.Render();
		window.Display();
	}
	CHECK(animationSuccessful 	== true);
	CHECK(progressBarSuccessful == true);

	//CHECK_NOTHROW(window.Cleanup());

	SDL_Quit();
}
