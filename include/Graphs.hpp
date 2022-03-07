#pragma once
#include <vector>
#include "Utils.hpp"

namespace Birb
{
	namespace Widgets
	{
		enum GraphType
		{
			Block, Line
		};

		struct Graph
		{
			Graph();
			Graph(const GraphType& graphType, const Rect& rect);
			Graph(const GraphType& graphType, const std::vector<double>& values, const Rect& rect);
			void Render();

			GraphType type;
			Rect rect;

			/* Colors */
			SDL_Color borderColor;
			SDL_Color backgroundColor;
			SDL_Color graphColor;

			std::vector<double> values;
			int borderSize;
			double wallOffset = 5.0;
		};
	}
}
