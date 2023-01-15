#include "Entities/Image.hpp"
#include "Values.hpp"
#include "Render.hpp"

namespace Birb
{
	namespace Entity
	{
		Image::Image()
		:sprite(Global::Placeholder::empty_texture)
		{}

		Image::Image(Texture& texture, const Rect& rect)
		:sprite(texture), angle(0.0f)
		{
			this->rect = rect;
		}

		void Image::RenderFunc()
		{
			Render::DrawTexture(sprite, rect, world_space, angle);
		}
	}
}
