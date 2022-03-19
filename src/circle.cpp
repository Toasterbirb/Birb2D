#include "Circle.hpp"
#include "Renderwindow.hpp"

#define PI 3.141592654

namespace Birb
{
	Circle::Circle()
	{
		radius = 0;
		pos = {0, 0};
		color = 0xFFFFFF;
	}

	Circle::Circle(const float& radius)
	:radius(radius)
	{
		pos = {0, 0};
		color = 0xFFFFFF;
	}

	Circle::Circle(const float& radius, const Vector2int& pos, Color color)
	:radius(radius), pos(pos), color(color)
	{}

	float Circle::Circumference()
	{
		return (radius * 2 * PI);
	}

	float Circle::Diameter()
	{
		return (radius * 2);
	}

	void Circle::RenderFunc()
	{
		Render::DrawCircle(color, pos, radius);
	}
}
