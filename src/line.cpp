#include "Line.hpp"
#include "Renderwindow.hpp"
#include "Logger.hpp"

namespace Birb
{
	void Line::DefaultLineValues()
	{
		color = Color(0xFFFFFF);
		thickness = 1;
	}

	Line::Line()
	{
		pointA = Vector2f(0, 0);
		pointB = Vector2f(0, 0);
		DefaultLineValues();
	}

	Line::Line(const Vector2f& pointA, const Vector2f& pointB)
	:pointA(pointA), pointB(pointB)
	{
		DefaultLineValues();
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
		if (thickness == 1)
			Render::DrawLine(*this);
		else if (thickness > 1)
			Render::DrawLine(*this, thickness);
		else
			Debug::Log("Tried to render a line with thickness <=0", Debug::error);
	}

	void Line::SetPos(const Vector2f& delta)
	{
		pointA = pointA + delta;
		pointB = pointB + delta;
	}
}
