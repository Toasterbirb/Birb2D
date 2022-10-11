#include "Line.hpp"
#include "Rect.hpp"
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
		pointA = Vector2(0, 0);
		pointB = Vector2(0, 0);
		DefaultLineValues();
	}

	Line::Line(const Vector2& pointA, const Vector2& pointB)
	:pointA(pointA), pointB(pointB)
	{
		DefaultLineValues();
	}

	Line::Line(const Vector2& pointA, const Vector2& pointB, const Color& color)
	:pointA(pointA), pointB(pointB), color(color)
	{}

	Line::Line(const Vector2& pointA, const Vector2& pointB, const Color& color, const int& renderingPriority)
	:pointA(pointA), pointB(pointB), color(color)
	{
		this->renderingPriority = renderingPriority;
	}

	double Line::length() const
	{
		return Math::VectorDistance(pointA, pointB);
	}

	Rect Line::boundingBox() const
	{
		/* Find the top left most point */
		Rect result;

		if (pointA.x <= pointB.x && pointA.y <= pointB.y)
		{
			result = pointA;
			result.w = pointB.x - pointA.x;
			result.h = pointB.y - pointA.y;
		}
		else
		{
			result = pointB;
			result.w = pointA.x - pointB.x;
			result.h = pointA.y - pointB.y;
		}


		return result;
	}

	void Line::RenderFunc()
	{
		/* Don't draw invisible lines */
		if (pointA == pointB)
			return;

		if (thickness == 1)
			Render::DrawLine(*this);
		else if (thickness > 1)
			Render::DrawLine(*this, thickness);
		else
			Debug::Log("Tried to render a line with thickness <=0", Debug::error);
	}

	void Line::SetPos(const Vector2& delta)
	{
		pointA = pointA + delta;
		pointB = pointB + delta;
	}
}
