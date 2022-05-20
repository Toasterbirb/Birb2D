#ifdef LIB_SDL
//#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#endif /* LIB_SDL */

#include "Logger.hpp"
#include "Render.hpp"

namespace Birb
{
	namespace Render
	{
#ifdef LIB_SDL
		void ResetDrawColor()
		{
			SDL_SetRenderDrawColor(Global::RenderVars::Renderer, Global::RenderVars::BackgroundColor.r, Global::RenderVars::BackgroundColor.g, Global::RenderVars::BackgroundColor.b, 255);
		}

		void SetRenderDrawColor(const Color& color)
		{
			SDL_SetRenderDrawColor(Global::RenderVars::Renderer, color.r, color.g, color.b, color.a);
		}
#endif /* LIB_SDL */

		void DrawRect(const Color& color, const Rect& dimensions)
		{
#ifdef LIB_SDL
			SetRenderDrawColor(color);
			SDL_Rect rectangle = dimensions.getSDLRect();
			SDL_RenderFillRect(Global::RenderVars::Renderer, &rectangle);
			ResetDrawColor();
#else /* LIB_SDL */
			Debug::Log("DrawRect()", Debug::fixme);
#endif /* LIB_SDL */
		}

		void DrawRect(const Color& color, const Rect& dimensions, const int& width)
		{
			DrawRect(color, Rect(dimensions.x, dimensions.y, dimensions.w, width)); /* Top */
			DrawRect(color, Rect(dimensions.x, dimensions.y + dimensions.h - width, dimensions.w, width)); /* Bottom */
			DrawRect(color, Rect(dimensions.x, dimensions.y, width, dimensions.h)); /* Left */
			DrawRect(color, Rect(dimensions.x + dimensions.w - width, dimensions.y, width, dimensions.h)); /* Right */
		}

		void DrawLine(const Color& color, const Vector2int& pointA, const Vector2int& pointB)
		{
#ifdef LIB_SDL
			SetRenderDrawColor(color);
			SDL_RenderDrawLine(Global::RenderVars::Renderer, pointA.x, pointA.y, pointB.x, pointB.y);
			ResetDrawColor();
#else
			Debug::Log("DrawLine()", Debug::fixme);
#endif /* LIB_SDL */
		}

		void DrawLine(const Color& color, const Vector2f& pointA, const Vector2f& pointB)
		{
#ifdef LIB_SDL
			SetRenderDrawColor(color);
			SDL_RenderDrawLineF(Global::RenderVars::Renderer, pointA.x, pointA.y, pointB.x, pointB.y);
			ResetDrawColor();
#else
			Debug::Log("DrawLine()", Debug::fixme);
#endif /* LIB_SDL */
		}

		void DrawLine(const Line& line)
		{
#ifdef LIB_SDL
			SetRenderDrawColor(line.color);
			SDL_RenderDrawLineF(Global::RenderVars::Renderer, line.pointA.x, line.pointA.y, line.pointB.x, line.pointB.y);
			ResetDrawColor();
#else
			Debug::Log("DrawLine()", Debug::fixme);
#endif /* LIB_SDL */
		}

		void DrawLine(const Line& line, const int& thickness)
		{
			/* Use a polygon to draw a thicker line */
			const int POINT_COUNT = 4;
			float pointOffset = thickness / 2.0;
			Vector2f points[POINT_COUNT] = {
				{ line.pointA.x - pointOffset, line.pointA.y - pointOffset },
				{ line.pointA.x + pointOffset, line.pointA.y + pointOffset },
				{ line.pointB.x + pointOffset, line.pointB.y + pointOffset },
				{ line.pointB.x - pointOffset, line.pointB.y - pointOffset },
			};
			DrawPolygon(line.color, points, POINT_COUNT);
		}

		void DrawLines(const Color& color, Vector2int* points, const int& pointCount)
		{
#ifdef LIB_SDL
			SDL_Point sdlPoints[pointCount];
			for (int i = 0; i < pointCount; i++)
			{
				sdlPoints[i] = { points[i].x, points[i].y };
			}

			SetRenderDrawColor(color);
			SDL_RenderDrawLines(Global::RenderVars::Renderer, sdlPoints, pointCount);
			ResetDrawColor();
#else
			Debug::Log("DrawLines()", Debug::fixme);
#endif /* LIB_SDL */
		}

		void DrawLines(const Color& color, Vector2f* points, const int& pointCount)
		{
#ifdef LIB_SDL
			SDL_FPoint sdlPoints[pointCount];
			for (int i = 0; i < pointCount; i++)
			{
				sdlPoints[i] = { points[i].x, points[i].y };
			}

			SetRenderDrawColor(color);
			SDL_RenderDrawLinesF(Global::RenderVars::Renderer, sdlPoints, pointCount);
			ResetDrawColor();
#else
			Debug::Log("DrawLines()", Debug::fixme);
#endif /* LIB_SDL */
		}

		bool DrawCircle(const Circle& circle)
		{
			return DrawCircle(circle.color, circle.pos, circle.radius);
		}

		bool DrawCircle(const Color& color, const Vector2int& pos, const int& radius)
		{
#ifdef LIB_SDL
			Uint32 uColor = (255<<24) + (int(color.b)<<16) + (int(color.g)<<8) + int(color.r);;
			if (filledCircleColor(Global::RenderVars::Renderer, pos.x, pos.y, radius, uColor) == 0)
			{
				Render::ResetDrawColor();
				return true;
			}
			else
			{
				Debug::Log("Error when drawing a circle", Debug::error);
				return false;
			}
#else
			Debug::Log("DrawCircle()", Debug::fixme);
			return false;
#endif /* LIB_SDL */
		}

		bool DrawPolygon(const Color& color, Vector2int* points, const int& pointCount)
		{
#ifdef LIB_SDL
			Uint32 uColor = (255<<24) + (int(color.b)<<16) + (int(color.g)<<8) + int(color.r);;

			/* Convert Vector2int points into Sint16 vectors */
			Sint16 vx[pointCount];
			Sint16 vy[pointCount];
			for (int i = 0; i < pointCount; i++)
			{
				vx[i] = points[i].x;
				vy[i] = points[i].y;
			}

			if (filledPolygonColor(Global::RenderVars::Renderer, vx, vy, pointCount, uColor) == 0)
			{
				Render::ResetDrawColor();
				return true;
			}
			else
			{
				Debug::Log("Error when drawing a polygon!", Debug::error);
				return false;
			}
#else
			Debug::Log("DrawPolygon()", Debug::fixme);
			return false;
#endif /* LIB_SDL */
		}

		bool DrawPolygon(const Color& color, const std::vector<Vector2int>& points)
		{
#ifdef LIB_SDL
			Uint32 uColor = (255<<24) + (int(color.b)<<16) + (int(color.g)<<8) + int(color.r);;

			/* Convert Vector2int points into Sint16 vectors */
			Sint16 vx[points.size()];
			Sint16 vy[points.size()];
			for (int i = 0; i < points.size(); i++)
			{
				vx[i] = points[i].x;
				vy[i] = points[i].y;
			}

			if (filledPolygonColor(Global::RenderVars::Renderer, vx, vy, points.size(), uColor) == 0)
			{
				Render::ResetDrawColor();
				return true;
			}
			else
			{
				Debug::Log("Error when drawing a polygon!", Debug::error);
				return false;
			}
#else
			Debug::Log("DrawPolygon()", Debug::fixme);
			return false;
#endif /* LIB_SDL */
		}

		/* filledPolygonColor works only with integers, so this will just
		 * round the floating point vlues into integers */
		bool DrawPolygon(const Color& color, Vector2f* points, const int& pointCount)
		{
			Vector2int intPoints[pointCount];
			for (int i = 0; i < pointCount; i++)
			{
				intPoints[i].x = std::round(points[i].x);
				intPoints[i].y = std::round(points[i].y);
			}
			return DrawPolygon(color, intPoints, pointCount);
		}

		bool DrawPolygon(const Color& color, const std::vector<Vector2f>& points)
		{
			Vector2int intPoints[points.size()];
			for (int i = 0; i < points.size(); i++)
			{
				intPoints[i].x = std::round(points[i].x);
				intPoints[i].y = std::round(points[i].y);
			}
			return DrawPolygon(color, intPoints, points.size());
		}

		bool DrawPolygon(const Polygon& polygon)
		{
			return DrawPolygon(polygon.color, polygon.points);
		}
	}
}
