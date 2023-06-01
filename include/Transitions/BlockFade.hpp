#pragma once

#include "Color.hpp"
#include "Rect.hpp"
#include "Transition.hpp"
#include "Vector/Vector2Int.hpp"
#include <vector>

namespace Birb
{
	namespace Transition
	{
		class BlockFade : public BaseTransition
		{
		public:
			BlockFade(const Color& color, int scale);
			virtual ~BlockFade();

			void draw(float progress);
			void set_color(const Color& color);

		private:
			Vector2Int block_count;
			std::vector<Rect> blocks;
			int total_color; /* Total amount of "color" it takes to max out the alpha in all blocks */
		};
	}
}
