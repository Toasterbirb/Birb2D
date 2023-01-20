#include "Entities/Empty.hpp"
#include "Render.hpp"

namespace Birb
{
	namespace Entity
	{
		Empty::Empty() {}
		Empty::Empty(const std::string& name)
		{
			this->name = name;
		}

		void Empty::RenderFunc()
		{
			Render::DrawRect(rect);
		}

		void Empty::SetPos(const Vector2& delta)
		{
			rect.x += delta.x;
			rect.y += delta.y;
		}
	}
}
