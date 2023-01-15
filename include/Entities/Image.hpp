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

			/// This is here just for compatiblitys sake
			Image(const std::string& name, const Vector2Int& pos, Texture& texture);

			/// This is here just for compatiblitys sake
			Image(const std::string& name, const Rect& rect, Texture& texture);

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
