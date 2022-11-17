#include "microprofile.h"
#include "Render.hpp"

#define PROFILER_GROUP "Rendering"
#define PROFILER_COLOR MP_LIGHTBLUE

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
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw rect", PROFILER_COLOR);
			SetRenderDrawColor(color);
			SDL_Rect rectangle = dimensions.getSDLRect();
			rectangle.x -= (Global::RenderVars::CameraPosition.x * dimensions.world_space * dimensions.parallax_multiplier);
			rectangle.y -= (Global::RenderVars::CameraPosition.y * dimensions.world_space * dimensions.parallax_multiplier);
			SDL_RenderFillRect(Global::RenderVars::Renderer, &rectangle);
			ResetDrawColor();
		}

		void DrawRect(const Color& color, const Rect& dimensions, const int& width)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw hollow rect", PROFILER_COLOR);
			DrawRect(color, Rect(dimensions.x, dimensions.y, dimensions.w, width)); /* Top */
			DrawRect(color, Rect(dimensions.x, dimensions.y + dimensions.h - width, dimensions.w, width)); /* Bottom */
			DrawRect(color, Rect(dimensions.x, dimensions.y, width, dimensions.h)); /* Left */
			DrawRect(color, Rect(dimensions.x + dimensions.w - width, dimensions.y, width, dimensions.h)); /* Right */
		}

		void DrawLine(const Color& color, const Vector2Int& pointA, const Vector2Int& pointB, const bool& world_space, const float& parallax_multiplier)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw line (int)", PROFILER_COLOR);
			SetRenderDrawColor(color);
			SDL_RenderDrawLine(Global::RenderVars::Renderer,
					pointA.x - (Global::RenderVars::CameraPosition.x * world_space * parallax_multiplier),
					pointA.y - (Global::RenderVars::CameraPosition.y * world_space * parallax_multiplier),
					pointB.x - (Global::RenderVars::CameraPosition.x * world_space * parallax_multiplier),
					pointB.y - (Global::RenderVars::CameraPosition.y * world_space * parallax_multiplier));
			ResetDrawColor();
		}

		void DrawLine(const Color& color, const Vector2& pointA, const Vector2& pointB, const bool& world_space, const float& parallax_multiplier)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw line (float)", PROFILER_COLOR);
			SetRenderDrawColor(color);
			SDL_RenderDrawLineF(Global::RenderVars::Renderer,
					pointA.x - (Global::RenderVars::CameraPosition.x * world_space * parallax_multiplier),
					pointA.y - (Global::RenderVars::CameraPosition.y * world_space * parallax_multiplier),
					pointB.x - (Global::RenderVars::CameraPosition.x * world_space * parallax_multiplier),
					pointB.y - (Global::RenderVars::CameraPosition.y * world_space * parallax_multiplier));
			ResetDrawColor();
		}

		void DrawLine(const Line& line)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw line (float)", PROFILER_COLOR);
			SetRenderDrawColor(line.color);
			SDL_RenderDrawLineF(Global::RenderVars::Renderer,
					line.pointA.x - (Global::RenderVars::CameraPosition.x * line.world_space),
					line.pointA.y - (Global::RenderVars::CameraPosition.y * line.world_space),
					line.pointB.x - (Global::RenderVars::CameraPosition.x * line.world_space),
					line.pointB.y - (Global::RenderVars::CameraPosition.y * line.world_space));
			ResetDrawColor();
		}

		void DrawLine(const Line& line, const int& thickness)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw polygon line", PROFILER_COLOR);
			/* Use a polygon to draw a thicker line */
			const int POINT_COUNT = 4;
			float pointOffset = thickness / 2.0;
			Vector2 points[POINT_COUNT] = {
				{ line.pointA.x - pointOffset, line.pointA.y - pointOffset },
				{ line.pointA.x + pointOffset, line.pointA.y + pointOffset },
				{ line.pointB.x + pointOffset, line.pointB.y + pointOffset },
				{ line.pointB.x - pointOffset, line.pointB.y - pointOffset },
			};
			DrawPolygon(line.color, points, POINT_COUNT, line.world_space);
		}

		void DrawLines(const Color& color, Vector2Int* points, const int& pointCount, const bool& world_space, const float& parallax_multiplier)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw multiple lines", PROFILER_COLOR);
			SDL_Point* sdlPoints = new SDL_Point[pointCount];
			for (int i = 0; i < pointCount; ++i)
			{
				sdlPoints[i] = {
					points[i].x - static_cast<int>(Global::RenderVars::CameraPosition.x * world_space * parallax_multiplier),
					points[i].y - static_cast<int>(Global::RenderVars::CameraPosition.y * world_space * parallax_multiplier)
				};
			}

			SetRenderDrawColor(color);
			SDL_RenderDrawLines(Global::RenderVars::Renderer, sdlPoints, pointCount);
			delete[] sdlPoints;
			ResetDrawColor();
		}

		void DrawLines(const Color& color, Vector2* points, const int& pointCount, const bool& world_space, const float& parallax_multiplier)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw multiple lines", PROFILER_COLOR);
			SDL_FPoint* sdlPoints = new SDL_FPoint[pointCount];
			for (int i = 0; i < pointCount; ++i)
			{
				sdlPoints[i] = {
					points[i].x - (Global::RenderVars::CameraPosition.x * world_space * parallax_multiplier),
					points[i].y - (Global::RenderVars::CameraPosition.y * world_space * parallax_multiplier)
				};
			}

			SetRenderDrawColor(color);
			SDL_RenderDrawLinesF(Global::RenderVars::Renderer, sdlPoints, pointCount);
			delete[] sdlPoints;
			ResetDrawColor();
		}

		bool DrawCircle(const Circle& circle)
		{
			return DrawCircle(circle.color, circle.pos, circle.radius, circle.world_space);
		}

		bool DrawCircle(const Color& color, const Vector2Int& pos, const int& radius, const bool& world_space, const float& parallax_multiplier)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw multiple lines", PROFILER_COLOR);
			Uint32 uColor = (255<<24) + (int(color.b)<<16) + (int(color.g)<<8) + int(color.r);;
			if (filledCircleColor(Global::RenderVars::Renderer,
						pos.x - (Global::RenderVars::CameraPosition.x * world_space * parallax_multiplier),
						pos.y - (Global::RenderVars::CameraPosition.y * world_space * parallax_multiplier),
						radius, uColor) == 0)
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

		bool DrawPolygon(const Color& color, Vector2Int* points, const int& pointCount, const bool& world_space, const float& parallax_multiplier)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw polygon", PROFILER_COLOR);
			Uint32 uColor = (255<<24) + (int(color.b)<<16) + (int(color.g)<<8) + int(color.r);;

			/* Convert Vector2Int points into Sint16 vectors and add the camera offset */
			Sint16* vx = new Sint16[pointCount];
			Sint16* vy = new Sint16[pointCount];
			for (int i = 0; i < pointCount; ++i)
			{
				vx[i] = points[i].x - (Global::RenderVars::CameraPosition.x * world_space * parallax_multiplier);
				vy[i] = points[i].y - (Global::RenderVars::CameraPosition.y * world_space * parallax_multiplier);
			}

			if (filledPolygonColor(Global::RenderVars::Renderer, vx, vy, pointCount, uColor) == 0)
			{
				/* Cleanup */
				delete[] vx;
				delete[] vy;

				Render::ResetDrawColor();
				return true;
			}
			else
			{
				/* Cleanup */
				delete[] vx;
				delete[] vy;

				Debug::Log("Error when drawing a polygon!", Debug::error);
				return false;
			}
		}

		bool DrawPolygon(const Color& color, const std::vector<Vector2Int>& points, const bool& world_space, const float& parallax_multiplier)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw polygon", PROFILER_COLOR);
			Uint32 uColor = (255<<24) + (int(color.b)<<16) + (int(color.g)<<8) + int(color.r);;

			/* Convert Vector2Int points into Sint16 vectors and add the camera offset */
			Sint16* vx = new Sint16[points.size()];
			Sint16* vy = new Sint16[points.size()];
			for (size_t i = 0; i < points.size(); ++i)
			{
				vx[i] = points[i].x - (Global::RenderVars::CameraPosition.x * world_space * parallax_multiplier);
				vy[i] = points[i].y - (Global::RenderVars::CameraPosition.y * world_space * parallax_multiplier);
			}

			if (filledPolygonColor(Global::RenderVars::Renderer, vx, vy, points.size(), uColor) == 0)
			{
				/* Cleanup */
				delete[] vx;
				delete[] vy;

				Render::ResetDrawColor();
				return true;
			}
			else
			{
				/* Cleanup */
				delete[] vx;
				delete[] vy;

				Debug::Log("Error when drawing a polygon!", Debug::error);
				return false;
			}
		}

		/* filledPolygonColor works only with integers, so this will just
		 * round the floating point vlues into integers */
		bool DrawPolygon(const Color& color, Vector2* points, const int& pointCount, const bool& world_space, const float& parallax_multiplier)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw polygon", PROFILER_COLOR);
			Vector2Int* intPoints = new Vector2Int[pointCount];
			for (int i = 0; i < pointCount; ++i)
			{
				intPoints[i].x = std::round(points[i].x);
				intPoints[i].y = std::round(points[i].y);
			}
			bool success = DrawPolygon(color, intPoints, pointCount, world_space);
			delete[] intPoints;
			return success;
		}

		bool DrawPolygon(const Color& color, const std::vector<Vector2>& points, const bool& world_space, const float& parallax_multiplier)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw polygon", PROFILER_COLOR);
			Vector2Int* intPoints = new Vector2Int[points.size()];
			for (size_t i = 0; i < points.size(); ++i)
			{
				intPoints[i].x = std::round(points[i].x);
				intPoints[i].y = std::round(points[i].y);
			}
			bool success = DrawPolygon(color, intPoints, points.size(), world_space);
			delete[] intPoints;
			return success;
		}

		bool DrawPolygon(const Polygon& polygon)
		{
			return DrawPolygon(polygon.color, polygon.points, polygon.world_space);
		}
	}
}
