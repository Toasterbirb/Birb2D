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
			double zeroValue = 0;
			bool normalizedZeroValue = false; ///< Set to true for normalized min value
			int borderSize;
			double wallOffset = 5.0;
			double blockSpacing = 10;
		};
	}
}