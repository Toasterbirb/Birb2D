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

namespace Birb
{
	void start(Game& game);
	void input(Game& game);
	void update(Game& game);
	void render(Game& game);
	void post_render();
	void cleanup();

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
		Game game(window_options, start, input, update, render);
		game.post_render 	= post_render;
		game.cleanup 		= cleanup;
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

	void start(Game& game)
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

	void input(Game& game)
	{
		input_called = true;
	}

	void update(Game& game)
	{
		update_called = true;
		update_call_count++;

		/* Rotate the polygon */
		polygon_angle++;
		polygon.SetRotation(polygon_angle);
	}

	void render(Game& game)
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

	void post_render()
	{
		post_render_called = true;
		post_render_call_count++;

		/* Pan the camera */
		Global::RenderVars::CameraPosition.x -= game_ptr->time_step()->deltaTime * 100;
	}

	void cleanup()
	{
		cleanup_called = true;
		cleanup_call_count++;

		/* Reset the camera movement */
		Global::RenderVars::CameraPosition = Vector2(0, 0);
	}
}
