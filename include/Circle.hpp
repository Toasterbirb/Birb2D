#pragma once

#include "Color.hpp"
#include "SceneObject.hpp"
#include "Vector.hpp"

namespace Birb
{
	class Circle : public SceneObject
	{
	public:
		Circle();
		Circle(const float& radius);
		Circle(const float& radius, const Vector2int& pos, Color color = 0xFFFFFF);

		float Circumference();
		float Diameter();

		float radius;
		Vector2int pos;
		Color color;

	private:
		void RenderFunc() override;
	};
}
