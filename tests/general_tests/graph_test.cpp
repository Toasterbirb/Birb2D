#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "Game.hpp"
#include "Graphs.hpp"
#include "Timer.hpp"
#include "Values.hpp"
#include "doctest.h"
#include <vector>

using namespace Birb;

namespace BirbTest
{
	void graph_start(Game& game);
	void graph_input(Game& game);
	void graph_update(Game& game);
	void graph_render(Game& game);

	Timer graph_timer;
	Scene scene;

	TEST_CASE("Rendering: Graph comparison")
	{
		std::vector<double> values = {
			1.5, 12, 5.6, 2.7, 7, 6, 15
		};

		Widgets::Graph line_graph(Widgets::Line, values, Rect(300, 80, 256, 150));
		line_graph.graphColor 		= Colors::Nord::Aurora::nord14;
		line_graph.backgroundColor 	= Colors::Nord::PolarNight::nord0;
		line_graph.borderColor 		= Colors::Nord::PolarNight::nord2;
		line_graph.parallax_multiplier = 1.0f;

		Widgets::Graph block_graph(Widgets::Block, values, Rect(300, line_graph.rect.y + 200, 256, 150));
		block_graph.graphColor 		= Colors::Nord::Aurora::nord14;
		block_graph.backgroundColor 	= Colors::Nord::PolarNight::nord0;
		block_graph.borderColor 		= Colors::Nord::PolarNight::nord2;
		block_graph.parallax_multiplier = 2.0f;

		Widgets::Graph area_graph(Widgets::Area, values, Rect(300, block_graph.rect.y + 200, 256, 150));
		area_graph.graphColor 		= Colors::Nord::Aurora::nord14;
		area_graph.backgroundColor 	= Colors::Nord::PolarNight::nord0;
		area_graph.borderColor 		= Colors::Nord::PolarNight::nord2;
		area_graph.parallax_multiplier = 3.0f;

		SceneObject* graphs[] = { &line_graph, &block_graph, &area_graph };
		scene.AddObject(graphs, 3);

		Game::WindowOpts opts;
		opts.window_dimensions.x = 640;
		Game game(opts, graph_start, graph_input, graph_update, graph_render);
		game.Start();
	}

	void graph_start(Game& game)
	{
		graph_timer.Start();
	}

	void graph_input(Game& game)
	{

	}

	void graph_update(Game& game)
	{
		if (graph_timer.ElapsedSeconds() > 1.5f)
			game.application_running = false;

		Global::RenderVars::CameraPosition.x += game.time_step()->deltaTime * 50;
	}

	void graph_render(Game& game)
	{
		scene.Render();
	}
}
