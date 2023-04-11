#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "Birb2D.hpp"

using namespace Birb;

/* Function declarations */
static void start(Game& game);
static void input(Game& game);
static void update(Game& game);
static void render(Game& game);
static void post_render();
static void cleanup();

int main(void)
{
	Game::WindowOpts window_options;
	window_options.title 				= "Topdown controller test";
	window_options.window_dimensions 	= { 1280, 720 };
	window_options.refresh_rate 		= 75;
	window_options.resizable 			= false;

	Game game_loop(window_options, start, input, update, render);

	/* Optional extra functions */
	game_loop.post_render = post_render;
	game_loop.cleanup = cleanup;

	/* Start the game loop */
	game_loop.Start();

	return 0;
}

constexpr int BACKGROUND_COUNT = 40;
constexpr int BACKGROUND_SIZE = 32;
Scene background_scene;
Scene player_scene;
Rect background_rects[BACKGROUND_COUNT][BACKGROUND_COUNT];
Rect player;
CharacterController::TopDown* topdown_controller;;

/* start() is called before the game loop starts.
 * Useful for doing stuff that will only run once before
 * the game starts */
void start(Game& game)
{
	for (int i = 0; i < BACKGROUND_SIZE; ++i)
	{
		for (int j = 0; j < BACKGROUND_SIZE; ++j)
		{
			background_rects[i][j].x = i * BACKGROUND_COUNT;
			background_rects[i][j].y = j * BACKGROUND_COUNT;
			background_rects[i][j].w = BACKGROUND_SIZE;
			background_rects[i][j].h = BACKGROUND_SIZE;
			background_rects[i][j].color = Colors::Nord::PolarNight::nord1;
			background_scene.AddObject(background_rects[i][j]);
		}
	}

	player = Rect(256, 128, 64, 64, Colors::Nord::Aurora::nord14);
	player_scene.AddObject(player);

	topdown_controller = new CharacterController::TopDown(player.x, player.y, game.time_step());
}

/* input() is called at the beginning of the frame
 * before update(). Behind the curtains it does input
 * polling etc. and then passes the SDL_Event into
 * this function */
void input(Game& game)
{
	topdown_controller->ProcessInput();
}

/* update() is called after input has been handled and
 * before the frame gets rendered. Its useful for any game
 * logic that needs to be updated before rendering */
void update(Game& game)
{
	topdown_controller->UpdatePosition();
}

/* render() is called after update() has been finished.
 * Before it gets called, the window will be cleared and
 * after the function has finished running, the rendered frame
 * will be presented */
void render(Game& game)
{
	background_scene.Render();
	player_scene.Render();
}

/* post_render() will be called after rendering has finished
 * and the timestep stalling has started. On non-windows systems
 * this function call will be done on a separate thread, so you
 * could use it to do some extra preparations for the next frame
 * while the main thread is sitting around doing nothing
 * and waiting to maintain the correct frame rate */
void post_render()
{

}

/* cleanup() gets called after the game loop has finished running
 * and the application is getting closed. This is useful for doing any
 * cleanup that is necessary, like freeing heap allocations etc. */
void cleanup()
{
	delete topdown_controller;
}
