#include "Transitions/BlockFade.hpp"
#include "Render.hpp"
#include "Utils.hpp"
#include "Values.hpp"

namespace Birb
{
	namespace Transition
	{
		BlockFade::BlockFade(const Color& color, int scale)
		{
			/* NOTE: "scale" in this context means the block count horizontally */

			/* Calculate the amount of blocks needed to fill up the screen */
			float block_width = static_cast<float>(Global::RenderVars::WindowDimensions.x) / scale;
			float vertical_block_count = Global::RenderVars::WindowDimensions.y / block_width;

			block_count.x = scale;
			block_count.y = std::ceil(vertical_block_count);

			/* Allocate the blocks */
			blocks.resize(block_count.x * block_count.y);
			for (int i = 0; i < block_count.x; ++i)
			{
				for (int j = 0; j < block_count.y; ++j)
				{
					int index = utils::FlatIndex({i, j}, block_count);
					blocks[index] = Rect(i * block_width, j * block_width, block_width, block_width, color);
					blocks[index].color.a = 0;
				}
			}

			total_color = blocks.size() * 255;

			/* Shuffle the list so that the blocks change color in random order */
			Random::ShuffleVector(blocks);
		}

		BlockFade::~BlockFade() {}

		void BlockFade::draw(float progress)
		{
			/* How much color there is left to share to the blocks */
			int color_left = std::round(progress * total_color);

			for (size_t i = 0; i < blocks.size(); ++i)
			{
				if (color_left > 0)
				{
					if (color_left > 255)
						blocks[i].color.a = 255;
					else
						blocks[i].color.a = color_left;

					color_left -= 255;
				}
				else
				{
					blocks[i].color.a = 0;
				}

				Render::DrawRect(blocks[i]);
			}
		}

		void BlockFade::set_color(const Color& color)
		{
			for (size_t i = 0; i < blocks.size(); ++i)
			{
				blocks[i].color = color;
			}
		}
	}
}
