#ifdef LIB_GLFW
#include "Render.hpp"
#include "Logger.hpp"

namespace Birb
{
	namespace Render
	{
		void DrawRect(const Color& color, const Rect& dimensions)
		{
			Debug::Log("DrawRect()", Debug::fixme);
		}

		void DrawLine(const Color& color, const Vector2int& pointA, const Vector2int& pointB)
		{
			Debug::Log("DrawLine()", Debug::fixme);
		}

		void DrawLine(const Color& color, const Vector2f& pointA, const Vector2f& pointB)
		{
			Debug::Log("DrawLine()", Debug::fixme);
		}

		void DrawLine(const Line& line)
		{
			Debug::Log("DrawLine()", Debug::fixme);
		}

		void DrawLines(const Color& color, Vector2int* points, const int& pointCount)
		{
			Debug::Log("DrawLines()", Debug::fixme);
		}

		void DrawLines(const Color& color, Vector2f* points, const int& pointCount)
		{
			Debug::Log("DrawLines()", Debug::fixme);
		}

		bool DrawCircle(const Color& color, const Vector2int& pos, const int& radius)
		{
			Debug::Log("DrawCircle()", Debug::fixme);
			return false;
		}

		bool DrawPolygon(const Color& color, Vector2int* points, const int& pointCount)
		{
			Debug::Log("DrawPolygon()", Debug::fixme);
			return false;
		}

		bool DrawPolygon(const Color& color, const std::vector<Vector2int>& points)
		{
			Debug::Log("DrawPolygon()", Debug::fixme);
			return false;
		}
	}
}
#endif
