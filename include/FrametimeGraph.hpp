#pragma once
#include "Entities/Text.hpp"
//#include "BaseEntity.hpp"
#include "Graphs.hpp"
#include "Rect.hpp"
#include "Scene.hpp"
#include "Timestep.hpp"

namespace Birb
{
	namespace Diagnostics
	{
		/// Draws a graph that shows frametimehistory
		/// Also next to the graph it shows the current frametime and fps
		class FrametimeGraph
		{
		public:
			FrametimeGraph(const Rect& rect, const int& pointCount, TimeStep& timeStep);
			void Render();
			bool enabled;
			int pointCount;
			Rect rect;

			Font font;
			Entity::Text fps_text;
			Entity::Text frametime_text;
			Entity::Text framebudget_text;

		private:
			TimeStep& timeStep;
			Widgets::Graph graph;
			Scene scene;
		};
	}
}
