#pragma once

#include "BaseEntity.hpp"

namespace Birb
{
	namespace Entity
	{
		class Empty : public BaseEntity, public SceneObject
		{
		public:
			Empty();
			Empty(const std::string& name);

		private:
			void RenderFunc() override;
			void SetPos(const Vector2& delta) override;
		};
	}
}
