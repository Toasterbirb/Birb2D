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

	float Circle::Circumference() const
	{
		return (radius * 2 * PI);
	}

	float Circle::Diameter() const
	{
		return (radius * 2);
	}

	Rect Circle::toRect() const
	{
		return Rect(pos.x - radius, pos.y - radius, Diameter(), Diameter());
	}

	void Circle::RenderFunc()
	{
		Render::DrawCircle(color, pos, radius);
	}

	void Circle::SetPos(const Vector2f& delta)
	{
		pos.x += delta.x;
		pos.y += delta.y;
	}
}
