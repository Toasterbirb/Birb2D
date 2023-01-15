#pragma once

#include "Texture.hpp"
#include "BaseEntity.hpp"

namespace Birb
{
	namespace Entity
	{
		class Image : public BaseEntity
		{
		public:
			Image();
			Image(Texture& texture, const Rect& rect);

			Texture& sprite;
			float angle;

			Image& operator=(const Image& other)
			{
				this->sprite 	= other.sprite;
				this->angle 	= other.angle;
				return *this;
			}

		private:
			void RenderFunc() override;
		};
	}
}
