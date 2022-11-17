#include "Birb2D.hpp"

using namespace Birb;

int main(int argc, char** argv)
{
	Debug::Log("Creating the window");
	Window window("Birb2D project template", Vector2Int(1280, 720), 75, false);
	TimeStep timeStep;
	timeStep.Init(&window);

	SDL_ShowCursor(SDL_DISABLE);

	Debug::Log("Starting the game loop");

	Rect rect(50, 50, 180, 90, Colors::LightGray);
	rect.parallax_multiplier = 1.1f;

	Rect rect2(150, 65, 180, 250, Colors::Green);
	rect.parallax_multiplier = 1.2f;

	Font font("birb2d_res/fonts/manaspace/manaspc.ttf", 32);
	Entity hello_world("Text", Vector2Int(500, 90), EntityComponent::Text("Hello world", &font, &Colors::White));
	hello_world.parallax_multiplier = 1.5f;

	Entity hello_world2("Text", Vector2Int(50, 50), EntityComponent::Text("Hello world", &font, &Colors::LightGray));

	Scene uiscene;
	uiscene.world_space = false;
	uiscene.AddObject(&hello_world2);

	bool ApplicationRunning = true;
	while (ApplicationRunning)
	{
		timeStep.Start();
		while (timeStep.Running())
		{
			/* Handle input stuff */
			while (window.PollEvents())
			{
				window.EventTick(window.event, &ApplicationRunning);
			}

			timeStep.Step();
		}

		Global::RenderVars::CameraPosition = Vector2(window.CursorPosition().x - window.dimensions.x / 2.0, window.CursorPosition().y - window.dimensions.y / 2.0);

		window.Clear();
		/* Handle rendering */

		/* Draw the sprites and stuff */
		Render::DrawRect(rect.color, rect);
		Render::DrawRect(rect2.color, rect2);
		Render::DrawEntity(hello_world);
		uiscene.Render();

		/* Draw the cursor */
		Render::DrawCircle(Colors::White, window.CursorPosition(), 2, false);

		/* End of rendering */
		window.Display();

		timeStep.End();
	}

	return 0;
}
