#include "Line.hpp"
#include "Renderwindow.hpp"

namespace Birb
{
	Line::Line()
	{
		pointA = Vector2f(0, 0);
		pointB = Vector2f(0, 0);
		color = Color(0xFFFFFF);
	}
	
	Line::Line(const Vector2f& pointA, const Vector2f& pointB)
	:pointA(pointA), pointB(pointB)
	{
		color = Color(0xFFFFFF);
	}

	Line::Line(const Vector2f& pointA, const Vector2f& pointB, const Color& color)
	:pointA(pointA), pointB(pointB), color(color)
	{}

	Line::Line(const Vector2f& pointA, const Vector2f& pointB, const Color& color, const int& renderingPriority)
	:pointA(pointA), pointB(pointB), color(color)
	{
		this->renderingPriority = renderingPriority;
	}

	void Line::RenderFunc()
	{
		Render::DrawLine(*this);
	}

	void Line::SetPos(const Vector2f& delta)
	{
		pointA = pointA + delta;
		pointB = pointB + delta;
	}
}
