#include "Diagnostics.hpp"
#include "Render.hpp"
#include "Values.hpp"
#include "Utils.hpp"

namespace Birb
{
	namespace Diagnostics
	{
		FrametimeGraph::FrametimeGraph(const Rect& rect, const int& pointCount, TimeStep& timeStep)
		:pointCount(pointCount), rect(rect), timeStep(timeStep)
		{
			enabled = true;

			graph = Widgets::Graph(Widgets::GraphType::Line, rect);
			graph.backgroundColor 	= Colors::Black;
			graph.graphColor 		= Colors::White;
			graph.borderColor 		= Colors::White;
			graph.normalizedZeroValue = true;
			graph.world_space 		= false;
			graph.rect.world_space 	= false;

			font.LoadFont("birb2d_res/fonts/manaspace/manaspc.ttf", 14);
			fps_text.textComponent = EntityComponent::Text("", &font, &Colors::White);
			fps_text.rect.x = rect.x + rect.w + 8;
			fps_text.rect.y = rect.y + 8;
			fps_text.world_space = false;

			frametime_text.textComponent = EntityComponent::Text("", &font, &Colors::White);
			frametime_text.rect.x = rect.x + rect.w + 8;
			frametime_text.rect.y = rect.y + 32;
			frametime_text.world_space = false;

			framebudget_text.textComponent = EntityComponent::Text("", &font, &Colors::White);
			framebudget_text.rect.x = rect.x + rect.w + 8;
			framebudget_text.rect.y = rect.y + 56;
			framebudget_text.world_space = false;
		}

		void FrametimeGraph::Render()
		{
			/* Skip rendering if the graph is disableD */
			if (!enabled)
				return;

			/* Update values */
			if (static_cast<int>(graph.values.size()) < pointCount)
			{
				graph.values.push_back(timeStep.deltaTime * 1000);
			}
			else
			{
				/* Move everything back by one */
				for (size_t i = 0; i < graph.values.size() - 1; ++i)
				{
					graph.values[i] = graph.values[i + 1];
				}

				/* Set the last value to the new value */
				graph.values[graph.values.size() - 1] = timeStep.deltaTime * 1000;
			}

			/* Draw fps and frametime next to the graph */
			fps_text.SetText(utils::CleanDecimals(Math::Round(1.0f / timeStep.deltaTime, 2)) + "fps");
			frametime_text.SetText(utils::CleanDecimals(timeStep.deltaTime) + "ms");
			framebudget_text.SetText(utils::CleanDecimals(timeStep.FrameBudget()) + "%");

			Render::DrawEntity(fps_text);
			Render::DrawEntity(frametime_text);
			Render::DrawEntity(framebudget_text);

			graph.Render();
		}
	}
}
