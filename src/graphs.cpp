#include "Graphs.hpp"
#include "Renderwindow.hpp"
#include "Values.hpp"

namespace Birb
{
	namespace Widgets
	{
		Graph::Graph()
		{
			borderColor 	= Colors::White;
			backgroundColor = Colors::Black;
			graphColor 		= Colors::White;

			borderSize = 3;
		}

		Graph::Graph(const GraphType& graphType, const Rect& rect)
		{
			this->values = std::vector<double>(0);
			this->rect = rect;
			this->type = graphType;

			borderColor 	= Colors::White;
			backgroundColor = Colors::White;
			graphColor 		= Colors::White;

			borderSize = 3;
		}

		Graph::Graph(const GraphType& graphType, const std::vector<double>& values, const Rect& rect)
		{
			this->values = values;
			this->rect = rect;
			this->type = graphType;

			borderColor 	= Colors::White;
			backgroundColor = Colors::White;
			graphColor 		= Colors::White;

			borderSize = 3;
		}

		void Graph::Render()
		{
			/* Skip rendering the graph if its not active */
			if (!active)
				return;

			/* Only draw the border if there are <=1 points */
			if (values.size() <= 1)
			{
				Render::DrawRect(borderColor, rect, 3);
				return;
			}

			double width = rect.w - (wallOffset * 2);
			std::vector<Vector2> points(values.size());

			/* Calculate points */
			double highestValue = Math::FindHighestValue(values);
			double lowestValue;
			if (normalizedZeroValue)
				lowestValue = Math::FindLowestValue(values);
			else
				lowestValue = zeroValue;

			for (size_t i = 0; i < values.size(); ++i)
			{
				points[i].x = (((width / static_cast<int>(values.size())) * (i + 0.5))) + rect.x + wallOffset;
				points[i].y = Math::Normalize(values[i], highestValue, lowestValue, rect.h) + rect.y;
			}

			/* Draw the background if its not the same color as the graph color */
			if (backgroundColor.r != graphColor.r ||
					backgroundColor.g != graphColor.g ||
					backgroundColor.b != graphColor.b ||
					backgroundColor.a != graphColor.a)
				Render::DrawRect(backgroundColor, rect);

			/* Draw lines / blocks with the point positions */
			switch (type)
			{
				case (GraphType::Line):
					Render::DrawLines(graphColor, &points[0], values.size());
					break;

				case (GraphType::Block):
					for (size_t i = 0; i < values.size(); ++i)
						Render::DrawRect(graphColor, Rect(points[i].x - (((width / static_cast<int>(values.size())) - blockSpacing) / 2), points[i].y, (width / values.size()) - blockSpacing, Math::Normalize(values[i], lowestValue, highestValue, rect.h)));
					break;

				case(GraphType::Area):
					/* Works pretty much the same way as the line rendering, but
					 * creates a polygon to fill in the area between the line and
					 * the bottom of the graph */

					Vector2 endBottomPoint(points[points.size() - 1].x, rect.y + rect.h);
					Vector2 startBottomPoint(points[0].x, rect.y + rect.h);

					/* End first, because we are working clockwise */
					points.push_back(endBottomPoint);
					points.push_back(startBottomPoint);

					Render::DrawPolygon(graphColor, points);
					break;
			}


			/* Draw the graph border */
			Render::DrawRect(borderColor, rect, 3);
		}

		void Graph::RenderFunc()
		{
			this->Render();
		}

		void Graph::SetPos(const Vector2& delta)
		{
			rect.x += delta.x;
			rect.y += delta.y;
		}
	}
}
