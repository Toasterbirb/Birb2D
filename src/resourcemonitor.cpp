#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "Logger.hpp"
#include "Render.hpp"
#include "ResourceMonitor.hpp"
#include "Timestep.hpp"


namespace Birb
{
	namespace Diagnostics
	{
		ResourceMonitor::ResourceMonitor()
		{
			ResourceMonitor::EntityCount = 0;
		}

		ResourceMonitor::ResourceMonitor(TimeStep* timestep)
		{
			ResourceMonitor::EntityCount = 0;
			scene.world_space = false;

			/* Load the debug font */
			debug_text_font = new Font("birb2d_res/fonts/freefont/FreeMonoBold.ttf", 14);

			/* Create the text entity */
			//EntityComponent::Text text_component("NULL", debug_text_font, &Colors::Nord::Frost::nord9, &Colors::Nord::PolarNight::nord0);
			//debug_text_entity = Entity("Debug text", Vector2Int(0, 0), text_component, 1);
			debug_text_entity = new Entity::Text("NULL", debug_text_font, Colors::Nord::Frost::nord9, Colors::Nord::PolarNight::nord0);
			debug_text_entity->rect = Vector2Int(0, 0);
			debug_text_entity->renderingPriority = 1;
			debug_text_entity->world_space = false;
			scene.AddObject(debug_text_entity);

#ifndef __WINDOWS__
			/* Get our own PID */
			PID = RUSAGE_SELF;
#endif

			ResourceMonitor::timestep = timestep;

			/* Reset the fps values */
			for (int i = 0; i < framerate_avg_accuracy; ++i)
				rolling_framerate_list[i] = 0;

			current_framerate_index = 0;

			/* Do error checking */
			if (debug_text_entity->ErrorFuseStatus())
				BlowErrorFuse();
		}

		void ResourceMonitor::Refresh()
		{
			/* Get all of the required data */
			float fps = 1.0f / timestep->deltaTime;
			rolling_framerate_list[current_framerate_index++] = fps;
			if (current_framerate_index > framerate_avg_accuracy - 1)
				current_framerate_index = 0;

			float lowest_framerate = rolling_framerate_list[0];
			float fps_total = 0;
			for (int i = 0; i < framerate_avg_accuracy; ++i)
			{
				fps_total += rolling_framerate_list[i];

				if (lowest_framerate > rolling_framerate_list[i])
					lowest_framerate = rolling_framerate_list[i];
			}

			float fps_average = fps_total / framerate_avg_accuracy;

			debug_text = "FPS: " + 				utils::CleanDecimals(Math::Round(fps, 1));
			debug_text += "\nFPS avg.: " + 		utils::CleanDecimals(Math::Round(fps_average, 1));
			debug_text += "\nFPS 1% low: " + 	utils::CleanDecimals(Math::Round(lowest_framerate, 1));
			debug_text += "\nFramebudget: " + 	utils::CleanDecimals(Math::Round(timestep->FrameBudget(), 1)) + "%";
			debug_text += "\nEntity count: " + 	std::to_string(ResourceMonitor::EntityCount);


#ifndef __WINDOWS__
			getrusage(PID, &memory_usage);
			long resident_memory_usage = memory_usage.ru_maxrss;

			debug_text += "\n\nMemory usage: " + std::to_string(resident_memory_usage / 1024) + " MB";
#endif
		}

		void ResourceMonitor::Render()
		{
			debug_text_entity->SetText(debug_text);

			/* Make sure that the debug text updated properly */
			if (debug_text_entity->ErrorFuseStatus())
				BlowErrorFuse();

			scene.Render();
		}

		void ResourceMonitor::Free()
		{
			delete debug_text_font;
			delete debug_text_entity;
		}
	}
}
