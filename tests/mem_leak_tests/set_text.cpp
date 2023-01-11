#include "Birb2D.hpp"
#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace Birb;

/* Function declarations */
static void start(Game& game);
static void input(Game& game);
static void update(Game& game);
static void render(Game& game);
static void post_render();
static void cleanup();

Entity text;
Entity text_2;
Font* font;
int counter = 0;

int main(int argc, char** argv)
{
	Game::WindowOpts window_options;
	window_options.title 				= "Transparent window (maybe)";
	window_options.window_dimensions 	= { 1280, 720 };
	window_options.refresh_rate 		= 500;
	window_options.resizable 			= false;

	Game game_loop(window_options, start, input, update, render);

	/* Optional extra functions */
	game_loop.post_render = post_render;
	game_loop.cleanup = cleanup;

	/* Start the game loop */
	game_loop.Start();

	return 0;
}

/* start() is called before the game loop starts.
 * Useful for doing stuff that will only run once before
 * the game starts */
void start(Game& game)
{
	font = new Font("fonts/freefont/FreeMonoBold.ttf", 64);
	EntityComponent::Text component_with_background("0", font, &Colors::Nord::Frost::nord9, &Colors::Nord::PolarNight::nord0);
	text = Entity("Text", Vector2Int(128, 128), component_with_background);

	EntityComponent::Text component("0", font, &Colors::Nord::Frost::nord9);
	text_2 = Entity("Text", Vector2Int(128, 256), component);

	/* Enable the resource monitor to check if there's a memory leak */
	Diagnostics::Debugging::Overlays::ResourceMonitor = true;
}

/* input() is called at the beginning of the frame
 * before update(). Behind the curtains it does input
 * polling etc. and then passes the SDL_Event into
 * this function */
void input(Game& game)
{

}

/* update() is called after input has been handled and
 * before the frame gets rendered. Its useful for any game
 * logic that needs to be updated before rendering */
void update(Game& game)
{
	counter++;
	text.SetText(std::to_string(counter));
	text_2.SetText(std::to_string(counter));
}

/* render() is called after update() has been finished.
 * Before it gets called, the window will be cleared and
 * after the function has finished running, the rendered frame
 * will be presented */
void render(Game& game)
{
	Render::DrawEntity(text);
	Render::DrawEntity(text_2);
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

}
