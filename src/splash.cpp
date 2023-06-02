#include "AssetManager.hpp"
#include "Random.hpp"
#include "Splash.hpp"
#include "Texture.hpp"
#include "Timer.hpp"
#include "Timestep.hpp"
#include "Values.hpp"

namespace Birb
{
	static const std::string res_base_path = "birb2d_res";

	Splash::Splash(Window& window, bool isCustom)
	:duration(2.0f), isCustom(false), window(window)
	{
#ifdef BUNDLED_ASSETS
		if (AssetManager::asset_list.size() == 0)
			Debug::Log("Bundled assets have been enabled but no assets were loaded. Did you forget to initialize bundled assets?", Debug::fixme);
#endif

		if (!isCustom)
		{
			loading_text = "Loading...";

			background_plane = Rect(0, 0, window.dimensions.x, window.dimensions.y);
			background_plane.color = 0xaab9bd;
			background_plane.renderingPriority = -1;

			asset_manager.LoadTexture("logo", res_base_path + "/logo.png");
			assert(asset_manager.texture("logo").isLoaded());
			float birb_tex_height = static_cast<float>(window.dimensions.y) / asset_manager.texture("logo").dimensions().y * 2;
			float size_multiplier = birb_tex_height / asset_manager.texture("logo").dimensions().y;

			Rect logo_rect(window.dimensions.x / 3.0 - asset_manager.texture("logo").dimensions().x * 2.0,
				window.dimensions.y / 2.0 - asset_manager.texture("logo").dimensions().y * 4,
				asset_manager.texture("logo").dimensions().x * size_multiplier,
				birb_tex_height);

			birb2d_logo = Entity::Image(asset_manager.texture("logo"), logo_rect);
			assert(birb2d_logo.sprite.isLoaded());

			manaspace.LoadFont(res_base_path + "/fonts/manaspace/manaspc.ttf", static_cast<float>(window.dimensions.y) / asset_manager.texture("logo").dimensions().y - 4);
			assert(manaspace.isLoaded());
			//birb2d_text = Entity("Birb2D logo text",
			//		Vector2Int(birb2d_logo.rect.x + birb2d_logo.rect.w + 32, birb2d_logo.rect.y + (birb2d_logo.rect.y / 8)),
			//		EntityComponent::Text("", &manaspace, &Colors::White));
			birb2d_text = Entity::Text("", &manaspace, Colors::White);
			birb2d_text.rect = Vector2Int(birb2d_logo.rect.x + birb2d_logo.rect.w + 32, birb2d_logo.rect.y + (birb2d_logo.rect.y / 8));

			/* Avoid problems that come from rendering an entity with size of <= 0 */
			birb2d_text.rect.w = 1;
			birb2d_text.rect.h = 1;


			/* Add the entities into the scene */
			scene.AddObject(&birb2d_logo);
			scene.AddObject(&birb2d_text);
			scene.AddObject(&background_plane);
		}

	}

	void Splash::Run()
	{
		manaspace_small.LoadFont(res_base_path + "/fonts/manaspace/manaspc.ttf", 24);
		assert(manaspace_small.isLoaded());

		//loading_text_entity = Entity("Loading text",
		//		Vector2Int(32, 32),
		//		EntityComponent::Text(loading_text, &manaspace_small, &Colors::Black));
		loading_text_entity = Entity::Text(loading_text, &manaspace_small, Colors::Black);
		loading_text_entity.rect = Vector2Int(32, 32);

		loading_text_entity.renderingPriority = 10;
		loading_text_entity.active = false;
		loading_scene.AddObject(&loading_text_entity);

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

					/* Skip the splash screen if there's a mouse click or keyboard
					 * input of any kind */
					if (window.isMouseDown() || window.isKeyDown())
						splash_running = false;
				}

				timeStep.Step();
			}

			if (!isCustom)
			{
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
						}
						else if (static_cast<int>(glitch_timer.ElapsedSeconds()) % 5 == 0)
						{
							char c = rand.RandomInt(64, 123);
							title_text[text_iterator] = c;
						}
					}

					birb2d_text.SetText(title_text);
				}
			}

			window.Clear();
			/** Handle rendering **/

			scene.Render();

			/** End of rendering **/
			window.Display();
			timeStep.End();
		}

		/* Clear the window one more time and create a loading screen frame */
		loading_text_entity.active = true;
		window.Clear();
		scene.Render();
		loading_scene.Render();
		window.Display();

		/* Make sure that everythin went a-okay */
		if (birb2d_logo.ErrorFuseStatus() || birb2d_text.ErrorFuseStatus() || loading_text_entity.ErrorFuseStatus())
			BlowErrorFuse();
	}
}
