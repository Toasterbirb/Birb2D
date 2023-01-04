#pragma once

#include "Color.hpp"
#include "SceneObject.hpp"
#include "Vector/Vector2Int.hpp"

namespace Birb
{
	class Rect;

	class Circle : public SceneObject
	{
	public:
		Circle();
		Circle(const float& radius);
		Circle(const float& radius, const Vector2Int& pos, Color color = 0xFFFFFF);

		float Circumference() const;
		float Diameter() const;
		Rect toRect() const; ///< Returns a rect around the circle

		float radius;
		Vector2Int pos;
		Color color;

	private:
		void RenderFunc() override;
		void SetPos(const Vector2& delta) override;
	};
}
