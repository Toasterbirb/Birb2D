#include "Polygon.hpp"
#include "Render.hpp"
#include "SDL_ttf.h"
#include "Values.hpp"
#include "SDL_events.h"
#include "Timestep.hpp"
#include "Vector/Vector2.hpp"
#include "Vector/Vector2Int.hpp"
#include "doctest.h"
#include "Game.hpp"
#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace Birb;

namespace BirbTest
{
	void game_start(Game& game);
	void game_input(Game& game);
	void game_update(Game& game);
	void game_render(Game& game);
	void game_post_render();
	void game_cleanup();

	bool start_called 		= false;
	bool input_called 		= false;
	bool update_called 		= false;
	bool render_called 		= false;
	bool post_render_called = false;
	bool cleanup_called 	= false;

	int start_call_count 		= 0;
	int update_call_count 		= 0;
	int render_call_count 		= 0;
	int post_render_call_count 	= 0;
	int cleanup_call_count 		= 0;

	int frame_counter = 0;
	const int target_frame_count = 200;

	/* Stuff to render */
	Polygon polygon;
	int polygon_angle = 0;

	Game* game_ptr;

	TEST_CASE("Rendering: Game loop class")
	{
		/* Some window options */
		Game::WindowOpts window_options;
		window_options.title 				= "Test game";
		window_options.window_dimensions 	= Vector2Int(640, 480);
		window_options.refresh_rate 		= 80;
		window_options.resizable 			= false;

		/* Create the game object */
		Game game(window_options, game_start, game_input, game_update, game_render);
		game.post_render 	= game_post_render;
		game.cleanup 		= game_cleanup;
		game_ptr = &game;

		/* "Run" the game 200 frames */
		game.Start();

		CHECK(frame_counter == target_frame_count);

		CHECK(start_called);
		CHECK(input_called);
		CHECK(update_called);
		CHECK(render_called);
		CHECK(post_render_called);
		CHECK(cleanup_called);

		CHECK(start_call_count == 1);
		CHECK(update_call_count == target_frame_count);
		CHECK(render_call_count == target_frame_count);
		CHECK(post_render_call_count == target_frame_count);
		CHECK(cleanup_call_count == 1);

		/* Make sure that SDL_ttf was uninitialized */
		CHECK_FALSE(Global::IsInit::IsInit::SDL_ttf);
		CHECK(TTF_WasInit() == 0);
	}

	void game_start(Game& game)
	{
		start_called = true;
		start_call_count++;

		polygon.color = Colors::Nord::Aurora::nord14;

		/* Add points to the polygon */
		polygon.AddPoints({
			Vector2(32, 32),
			Vector2(128, 18),
			Vector2(256, 64),
			Vector2(200, 345),
			Vector2(40, 200)
		});
	}

	void game_input(Game& game)
	{
		input_called = true;
	}

	void game_update(Game& game)
	{
		update_called = true;
		update_call_count++;

		/* Rotate the polygon */
		polygon_angle++;
		polygon.SetRotation(polygon_angle);
	}

	void game_render(Game& game)
	{
		render_called = true;
		render_call_count++;
		frame_counter++;

		/* Render the polygon */
		Render::DrawPolygon(polygon);

		/* Check if the game should be stopped */
		if (frame_counter >= target_frame_count)
			game_ptr->application_running = false;
	}

	void game_post_render()
	{
		post_render_called = true;
		post_render_call_count++;

		/* Pan the camera */
		Global::RenderVars::CameraPosition.x -= game_ptr->time_step()->deltaTime * 100;
	}

	void game_cleanup()
	{
		cleanup_called = true;
		cleanup_call_count++;

		/* Reset the camera movement */
		Global::RenderVars::CameraPosition = Vector2(0, 0);
	}
}
