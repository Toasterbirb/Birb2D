#ifdef LIB_SDL
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Render.hpp"
#include "Logger.hpp"

namespace Birb
{
	namespace Render
	{
		void ResetDrawColor()
		{
			SDL_SetRenderDrawColor(Global::RenderVars::Renderer, Global::RenderVars::BackgroundColor.r, Global::RenderVars::BackgroundColor.g, Global::RenderVars::BackgroundColor.b, 255);
		}

		void SetRenderDrawColor(const Color& color)
		{
			SDL_SetRenderDrawColor(Global::RenderVars::Renderer, color.r, color.g, color.b, color.a);
		}

		void DrawRect(const Color& color, const Rect& dimensions)
		{
			SetRenderDrawColor(color);
			SDL_Rect rectangle = dimensions.getSDLRect();
			SDL_RenderFillRect(Global::RenderVars::Renderer, &rectangle);
			ResetDrawColor();
		}

		void DrawLine(const Color& color, const Vector2int& pointA, const Vector2int& pointB)
		{
			SetRenderDrawColor(color);
			SDL_RenderDrawLine(Global::RenderVars::Renderer, pointA.x, pointA.y, pointB.x, pointB.y);
			ResetDrawColor();
		}

		void DrawLine(const Color& color, const Vector2f& pointA, const Vector2f& pointB)
		{
			SetRenderDrawColor(color);
			SDL_RenderDrawLineF(Global::RenderVars::Renderer, pointA.x, pointA.y, pointB.x, pointB.y);
			ResetDrawColor();
		}

		void DrawLine(const Line& line)
		{
			DrawLine(line.color, line.pointA, line.pointB);
		}

		void DrawLines(const Color& color, Vector2int* points, const int& pointCount)
		{
			SDL_Point sdlPoints[pointCount];
			for (int i = 0; i < pointCount; i++)
			{
				sdlPoints[i] = { points[i].x, points[i].y };
			}

			SetRenderDrawColor(color);
			SDL_RenderDrawLines(Global::RenderVars::Renderer, sdlPoints, pointCount);
			ResetDrawColor();
		}

		void DrawLines(const Color& color, Vector2f* points, const int& pointCount)
		{
			SDL_FPoint sdlPoints[pointCount];
			for (int i = 0; i < pointCount; i++)
			{
				sdlPoints[i] = { points[i].x, points[i].y };
			}

			SetRenderDrawColor(color);
			SDL_RenderDrawLinesF(Global::RenderVars::Renderer, sdlPoints, pointCount);
			ResetDrawColor();
		}

		bool DrawCircle(const Color& color, const Vector2int& pos, const int& radius)
		{
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
		}

		bool DrawPolygon(const Color& color, Vector2int* points, const int& pointCount)
		{
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
		}

		bool DrawPolygon(const Color& color, const std::vector<Vector2int>& points)
		{
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
		}
	}
}
#endif
