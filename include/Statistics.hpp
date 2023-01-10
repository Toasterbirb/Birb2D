#pragma once

#include "Entity.hpp"
#include "Font.hpp"
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
	class Entity;
	class Font;
	class TimeStep;

	namespace Diagnostics
	{
		/// Draw a text overlay that shows some
		/// runtime performance statistics. Due to the nature of
		/// some statistics, some features are only available on Linux
		class Statistics : public SceneObject
		{
		public:
			Statistics();
			Statistics(TimeStep* timestep);

			/// Update all of the values
			void Refresh();
			void Render();
			void Free(); ///< Free the font

		private:
			Font* 			debug_text_font;
			Entity 			debug_text_entity;
			TimeStep* 		timestep;
			std::string 	debug_text;

#ifndef __WINDOWS__
			int PID;
			struct rusage memory_usage;
#endif

			void RenderFunc() override;
			void SetPos(const Vector2& delta) override;
		};
	}
}
