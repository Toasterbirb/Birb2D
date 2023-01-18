#pragma once

#include "Texture.hpp"
#include "BaseEntity.hpp"

namespace Birb
{
	namespace Entity
	{
		class Image : public BaseEntity, public SceneObject
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
				/* Base entity stuff */
				this->name 		= other.name;
				this->angle 	= other.angle;
				this->rect 		= other.rect;

				/* SceneObject stuff */
				this->renderingPriority 	= other.renderingPriority;
				this->active 				= other.active;
				this->parallax_multiplier 	= other.parallax_multiplier;
				this->world_space 			= other.world_space;

				this->sprite 	= other.sprite;
				this->angle 	= other.angle;
				return *this;
			}

		private:
			void RenderFunc() override;
			void SetPos(const Vector2& delta) override;
		};
	}
}
