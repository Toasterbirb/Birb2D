#pragma once

#include "Graphs.hpp"
#include "Timestep.hpp"

namespace Birb
{
	namespace Diagnostics
	{
		class FrametimeGraph
		{
		public:
			FrametimeGraph(const Rect& rect, const int& pointCount, TimeStep& timeStep);
			void Render();
			bool enabled;
			int pointCount;
			Rect rect;

		private:
			TimeStep& timeStep;
			Widgets::Graph graph;
		};

		/// Boolean toggles for debugging features. Some can clutter the console output
		/// quite a bit, so be careful
        struct Debugging
        {
            static inline bool Buttons = false;
        };

	}
}
