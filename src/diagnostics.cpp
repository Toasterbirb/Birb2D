#include "Diagnostics.hpp"
#include "Values.hpp"

namespace Birb
{
	namespace Diagnostics
	{
		FrametimeGraph::FrametimeGraph(const Rect& rect, const int& pointCount, TimeStep* timeStep)
		:timeStep(timeStep), pointCount(pointCount), rect(rect)
		{
			enabled = true;
			graph = Widgets::Graph(Widgets::GraphType::Line, rect);
			graph.backgroundColor 	= Colors::Black;
			graph.graphColor 		= Colors::White;
			graph.borderColor 		= Colors::White;
			graph.normalizedZeroValue = true;
		}

		void FrametimeGraph::Render()
		{
			/* Skip rendering if the graph is disableD */
			if (!enabled)
				return;
			
			/* Update values */
			if (graph.values.size() < pointCount)
			{
				graph.values.push_back(timeStep->deltaTime * 1000);
			}
			else
			{
				/* Move everything back by one */
				for (int i = 0; i < (int)graph.values.size() - 1; i++)
				{
					graph.values[i] = graph.values[i + 1];
				}
				
				/* Set the last value to the new value */
				graph.values[graph.values.size() - 1] = timeStep->deltaTime * 1000;
			}

			graph.Render();
		}
	}
}
