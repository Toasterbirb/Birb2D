#include "doctest.h"
#include "Circle.hpp"
#include "Entity.hpp"
#include "Font.hpp"
#include "Graphs.hpp"
#include "Math.hpp"
#include "Color.hpp"
#include "Values.hpp"
#include "Logger.hpp"
#include "Utils.hpp"
#include "Scene.hpp"
#include "Polygon.hpp"
#include "Renderwindow.hpp"

// This test is full of SDL stuff
TEST_CASE("Window and rendering functions")
{
	Birb::ApplicationInfo appInfo("Birb2D_tests");

	Birb::Window window("Title", Birb::Vector2Int(1280, 720), 60, false);
	SDL_Texture* texture 	= Birb::Resources::LoadTexture("textures/birb.png");
	Birb::Font font("fonts/freefont/FreeMonoBold.ttf", 32);

	Birb::Scene testScene;
	testScene.Activate();

	Birb::Entity testEntity("Test entity", Birb::Vector2Int(10, 10), texture);
	Birb::Entity secondEntityWithSameTexture("Second entity with the same texture", Birb::Rect(200, 400, 128 * 2, 72 * 2), texture);
	Birb::Entity rotatedEntity("Rotated entity with custom localscale", Birb::Rect(300, 100, 128, 72), texture);
	rotatedEntity.angle = 45;
	rotatedEntity.localScale = Birb::Vector2(3.5, 2);
	Birb::Entity entityWithNegativeSize("Entity with negative size", Birb::Rect(300, 100, -128, 72), texture);

	Birb::Line line(Birb::Vector2(0, 0), Birb::Vector2(1280, 720));
	line.renderingPriority = -1;

	Birb::Line lineB({0, 720}, {1280, 0});
	lineB.thickness = 10;

	Birb::Rect renderedRect(0, 0, 100, 100);
	renderedRect.renderingPriority = -5;

	Birb::Polygon polygon(
	{
		Birb::Vector2(0, 200),
		Birb::Vector2(200, 184),
		Birb::Vector2(230, 110),
		Birb::Vector2(0, 180)
	}, 0x81E176);

	Birb::Circle circle(32, {500, 650}, 0x32DDAA);

	/* Add entities etc. to the scene */
	testScene.AddObject(&testEntity);
	testScene.AddObject(&secondEntityWithSameTexture);
	testScene.AddObject(&rotatedEntity);
	testScene.AddObject(&line);
	testScene.AddObject(&lineB);
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

		CHECK(Birb::Render::DrawCircle(Birb::Colors::Blue, Birb::Vector2Int(400, 400), 50));
		CHECK_NOTHROW(Birb::Render::DrawLine(Birb::Colors::Red, Birb::Vector2Int(450, 600), Birb::Vector2Int(400, 200)));
		CHECK_NOTHROW(Birb::Render::DrawRect(Birb::Colors::Green, Birb::Rect(500, 500, 200, 20)));

		/* Draw a polygon */
		Birb::Vector2Int polyPoints[5] = {
			Birb::Vector2Int(100, 59),
			Birb::Vector2Int(150, 34),
			Birb::Vector2Int(170, 99),
			Birb::Vector2Int(87, 24),
			Birb::Vector2Int(53, 10),
		};
		CHECK(Birb::Render::DrawPolygon(Birb::Colors::White, polyPoints, 5));

		/* Draw the graphs */
		lineGraph.Render();
		blockGraph.Render();

	}
	CHECK_NOTHROW(window.Display());
	SDL_Delay(1000);

	/* Toggle the test scene */
	testScene.Toggle();

	CHECK_NOTHROW(window.Clear());
	{
		/* Draw a polygon */
		std::vector<Birb::Vector2Int> polyPoints2 = {
			Birb::Vector2Int(10, 5),
			Birb::Vector2Int(150, 34),
			Birb::Vector2Int(170, 99),
			Birb::Vector2Int(87, 24),
			Birb::Vector2Int(53, 10),
		};
		CHECK(Birb::Render::DrawPolygon(Birb::Colors::White, polyPoints2));

		testScene.Render();
		CHECK_FALSE(Birb::Render::DrawEntity(entityWithNegativeSize));

		CHECK(Birb::Render::DrawCircle(Birb::Colors::White, Birb::Vector2Int(400, 400), 50));
		CHECK_NOTHROW(Birb::Render::DrawLine(Birb::Colors::Red, Birb::Vector2Int(450, 600), Birb::Vector2Int(400, 200)));
		CHECK_NOTHROW(Birb::Render::DrawRect(Birb::Colors::Green, Birb::Rect(500, 500, 200, 20)));

		/* Draw the graph */
		lineGraph.Render();
		blockGraph.Render();

		/* Draw a thick line over everything */
		Birb::Render::DrawLine(lineB, 4);
	}

	CHECK_NOTHROW(window.Display());
	SDL_Delay(1000);

	SDL_Texture* animationSprite = Birb::Resources::LoadTexture("textures/birb_animation.png");
	Birb::Entity animationBirb(
			"Animated birb",
			Birb::Vector2Int(100, 100),
			animationSprite,
			Birb::EntityComponent::Animation(
				Birb::Vector2Int(64, 64),
				16,
				8,
				true));
	animationBirb.localScale = Birb::Vector2(3, 3);
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

	//SDL_Quit();
}
