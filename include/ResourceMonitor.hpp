#pragma once

#include "Entities/Text.hpp"
#include "Font.hpp"
#include "Input.hpp"
#include "SceneObject.hpp"

/* Linux only things */
#ifndef __WINDOWS__
#include <sys/resource.h>
#endif

#ifdef DISTCC
#include <string>
#endif

namespace Birb
{
	class TimeStep;

	namespace Diagnostics
	{
		/// Draw a text overlay that shows some
		/// runtime performance statistics. Due to the nature of
		/// some statistics, some features are only available on Linux
		class ResourceMonitor
		{
		public:
			ResourceMonitor();
			ResourceMonitor(TimeStep* timestep);

			/// Update all of the values
			void Refresh();
			void Render();
			void Free(); ///< Free the font

		private:
			Font* 			debug_text_font;
			Entity::Text 	debug_text_entity;
			TimeStep* 		timestep;
			std::string 	debug_text;

			static constexpr int 	framerate_avg_accuracy = 100;
			float 					rolling_framerate_list[framerate_avg_accuracy];
			int 					current_framerate_index;

#ifndef __WINDOWS__
			int PID;
			struct rusage memory_usage;
#endif
		};
	}
}
