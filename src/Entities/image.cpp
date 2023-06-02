#include "Entities/Image.hpp"
#include "Values.hpp"
#include "Render.hpp"

#include <iostream>

namespace Birb
{
	namespace Entity
	{
		Image::Image()
		:sprite(Global::Placeholder::empty_texture), angle(0.0f)
		{}

		Image::Image(Texture& texture, const Rect& rect)
		:sprite(texture), angle(0.0f)
		{
			this->rect = rect;
		}

		Image::~Image()
		{}

		Image::Image(const std::string& name, const Vector2Int& pos, Texture& texture)
		:sprite(texture), angle(0.0f)
		{
			this->name = name;
			this->rect = pos;
		}

		Image::Image(const std::string& name, const Rect& rect, Texture& texture)
		:sprite(texture), angle(0.0f)
		{
			this->name = name;
			this->rect = rect;
		}

		void Image::RenderFunc()
		{
			assert(sprite.isLoaded());
			if (!Render::DrawTexture(sprite, rect, world_space, angle))
				BlowErrorFuse();
		}

		void Image::SetPos(const Vector2& delta)
		{
			rect.x += delta.x;
			rect.y += delta.y;
		}
	}
}
