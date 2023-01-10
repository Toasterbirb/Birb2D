#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "Render.hpp"
#include "Statistics.hpp"
#include "Timestep.hpp"


namespace Birb
{
	namespace Diagnostics
	{
		Statistics::Statistics() {}

		Statistics::Statistics(TimeStep* timestep)
		{
			/* Load the debug font */
			debug_text_font = new Font("fonts/manaspace/manaspc.ttf", 14);

			/* Create the text entity */
			EntityComponent::Text text_component("NULL", debug_text_font, &Colors::Nord::Frost::nord9, &Colors::Nord::PolarNight::nord0);
			debug_text_entity = Entity("Debug text", Vector2Int(0, 0), text_component, 1);
			debug_text_entity.world_space = false;

#ifndef __WINDOWS__
			/* Get our own PID */
			PID = RUSAGE_SELF;
#endif

			Statistics::timestep = timestep;

			Refresh();
		}

		void Statistics::Refresh()
		{
			/* Get all of the required data */
			float fps = 1.0f / timestep->deltaTime;

#ifndef __WINDOWS__
			getrusage(PID, &memory_usage);
			long resident_memory_usage = memory_usage.ru_maxrss;
#endif

			debug_text = "FPS: " + utils::CleanDecimals(Math::Round(fps, 1));

#ifndef __WINDOWS__
			/* Linux version */
			debug_text += "\nMemory usage: " + std::to_string(resident_memory_usage / 1024) + " MB";
#endif
		}

		void Statistics::Render()
		{
			RenderFunc();
		}

		void Statistics::Free()
		{
			delete debug_text_font;
		}

		void Statistics::RenderFunc()
		{
			debug_text_entity.SetText(debug_text);
			Render::DrawEntity(debug_text_entity);
		}

		void Statistics::SetPos(const Vector2& delta)
		{
			/* Don't do anything. The statistics window is supposed to stick
			 * to the top left corner */
		}
	}
}
