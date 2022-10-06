#include "Splash.hpp"
#include "Texture.hpp"
#include "Timestep.hpp"
#include "Random.hpp"

namespace Birb
{
	Splash::Splash(Window& window)
	:duration(2.0f), insertLoadingScreenFrame(false), window(window)
	{
		std::string res_base_path = "./res/birb2d_res";

		background_plane = Entity("Background plane", Rect(0, 0, window.dimensions.x, window.dimensions.y));
		background_plane.rect.color = 0xaab9bd;
		background_plane.renderingPriority = -1;

		Texture birb2d_logo_tex(res_base_path + "/logo.png");
		float birb_tex_height = static_cast<float>(window.dimensions.y) / birb2d_logo_tex.dimensions().y * 2;
		float size_multiplier = birb_tex_height / birb2d_logo_tex.dimensions().y;
		birb2d_logo = Entity("Birb2D logo",
				Rect(window.dimensions.x / 3.0 - birb2d_logo_tex.dimensions().x * 2.0,
					window.dimensions.y / 2.0 - birb2d_logo_tex.dimensions().y * 4,
					birb2d_logo_tex.dimensions().x * size_multiplier,
					birb_tex_height),
				birb2d_logo_tex);


		manaspace.LoadFont(res_base_path + "/fonts/manaspace/manaspc.ttf", static_cast<float>(window.dimensions.y) / birb2d_logo_tex.dimensions().y - 4);
		birb2d_text = Entity("Birb2D logo text",
				Vector2Int(birb2d_logo.rect.x + birb2d_logo.rect.w + 32, birb2d_logo.rect.y + (birb2d_logo.rect.y / 8)),
				EntityComponent::Text("", &manaspace, &Colors::White));

		/* Avoid problems that come from rendering an entity with size of <= 0 */
		birb2d_text.rect.w = 1;
		birb2d_text.rect.h = 1;


		/* Add the entities into the scene */
		scene.AddObject(&birb2d_logo);
		scene.AddObject(&birb2d_text);
		scene.AddObject(&background_plane);
	}

	void Splash::Run()
	{
		/* Implement a simple rendering loop */
		TimeStep timeStep;
		timeStep.Init(&window);

		Timer splash_timer;
		splash_timer.Start();

		/* These variables is only used in the default splash */
		std::string title_text = " ";
		std::string target_text = "Birb2D";
		size_t text_iterator = 0;
		Random rand;
		Timer glitch_timer;
		glitch_timer.Start();

		bool splash_running = true;
		while (splash_running && splash_timer.ElapsedSeconds() < duration)
		{
			timeStep.Start();
			while (timeStep.Running())
			{
				while (window.PollEvents())
				{
					window.EventTick(window.event, &splash_running);
				}

				timeStep.Step();
			}

			if (splash_timer.ElapsedMilliseconds() > 250)
			{
				/* Update the glitchy text */
				if (text_iterator < target_text.size())
				{
					if (glitch_timer.ElapsedMilliseconds() > 100)
					{
						title_text[text_iterator] = target_text[text_iterator];
						title_text += " ";
						++text_iterator;
						glitch_timer.Start();
						std::cout << title_text << std::endl;
					}
					else if (static_cast<int>(glitch_timer.ElapsedSeconds()) % 5 == 0)
					{
						char c = rand.RandomInt(64, 123);
						title_text[text_iterator] = c;
					}
				}

				birb2d_text.SetText(title_text);
			}

			window.Clear();
			/** Handle rendering **/

			scene.Render();

			/** End of rendering **/
			window.Display();
			timeStep.End();
		}
	}
}
