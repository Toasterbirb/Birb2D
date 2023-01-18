#include "Circle.hpp"
#include "Logger.hpp"
#include "Polygon.hpp"
#include "Render.hpp"
#include "Values.hpp"
#include "microprofile.h"

#define PROFILER_GROUP "Rendering"
#define PROFILER_COLOR MP_LIGHTBLUE

namespace Birb
{
	namespace Render
	{
		/* Private function declarations */
		bool _DrawFilledPolygon(SDL_Renderer* renderer, Sint16* vx, Sint16* vy, int point_count, Uint32 color);

		void ResetDrawColor()
		{
			SDL_SetRenderDrawColor(Global::RenderVars::Renderer, Global::RenderVars::BackgroundColor.r, Global::RenderVars::BackgroundColor.g, Global::RenderVars::BackgroundColor.b, 255);
		}

		void SetRenderDrawColor(const Color& color)
		{
			SDL_SetRenderDrawColor(Global::RenderVars::Renderer, color.r, color.g, color.b, color.a);
		}

		bool DrawTexture(const Texture& texture, const Rect& rect, const bool& world_space, const float& angle)
		{
			SDL_Rect src;
			SDL_Rect dst;
			src.x = 0;
			src.y = 0;
			src.w = texture.dimensions().x;
			src.h = texture.dimensions().y;

			dst.x = rect.x - (Global::RenderVars::CameraPosition.x * world_space);
			dst.y = rect.y - (Global::RenderVars::CameraPosition.y * world_space);
			dst.w = rect.w; // * entity.localScale.x;
			dst.h = rect.h; // * entity.localScale.y;
			return DrawTexture(texture, src, dst, angle);
		}

		bool DrawTexture(const Texture& texture, const SDL_Rect& src, const SDL_Rect& dst, const float& angle)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw texture", PROFILER_COLOR);

			/* Make sure that the texture is loaded */
			if (!texture.isLoaded())
				return false;

			/* Get texture data */
			int texWidth 	= 0;
			int texHeight 	= 0;

			if (texture.dimensions().x <= 0 || texture.dimensions().y <= 0)
			{
				Birb::Debug::Log("Tried to render an entity with a texture with size of <= 0", Debug::Type::warning);
				return false;
			}

			Vector2Int centerPoint(texture.dimensions().x / 2, texture.dimensions().y / 2);
			SDL_Point center = { centerPoint.x, centerPoint.y };

			if (SDL_RenderCopyEx(Global::RenderVars::Renderer, texture.sdlTexture(), &src, &dst, angle, &center, SDL_FLIP_NONE) < 0)
			{
				Debug::Log("Error rendering a texture with dimensions [ " + texture.dimensions().ToString() + " ]. SDL Error: " + SDL_GetError(), Debug::error);
				return false;
			}
			else
			{
				return true;
			}

			return true;
		}

		bool DrawRect(const Rect& rect)
		{
			return DrawRect(rect.color, rect);
		}

		bool DrawRect(const Color& color, const Rect& dimensions)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw rect", PROFILER_COLOR);
			SetRenderDrawColor(color);
			SDL_Rect rectangle = dimensions.getSDLRect();
			rectangle.x -= (Global::RenderVars::CameraPosition.x * dimensions.world_space * dimensions.parallax_multiplier);
			rectangle.y -= (Global::RenderVars::CameraPosition.y * dimensions.world_space * dimensions.parallax_multiplier);
			bool success = SDL_RenderFillRect(Global::RenderVars::Renderer, &rectangle);
			ResetDrawColor();
			return success;
		}

		bool DrawRect(const Color& color, const Rect& dimensions, const int& width)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw hollow rect", PROFILER_COLOR);

			/* Create the rectangles */
			Rect top(dimensions.x, dimensions.y, dimensions.w, width);
			Rect bottom(dimensions.x, dimensions.y + dimensions.h - width, dimensions.w, width);
			Rect left(dimensions.x, dimensions.y, width, dimensions.h);
			Rect right(dimensions.x + dimensions.w - width, dimensions.y, width, dimensions.h);

			/* Set world_space and parallax values */
			top.world_space 	= dimensions.world_space;
			bottom.world_space 	= dimensions.world_space;
			left.world_space 	= dimensions.world_space;
			right.world_space 	= dimensions.world_space;

			top.parallax_multiplier 	= dimensions.parallax_multiplier;
			bottom.parallax_multiplier 	= dimensions.parallax_multiplier;
			left.parallax_multiplier 	= dimensions.parallax_multiplier;
			right.parallax_multiplier 	= dimensions.parallax_multiplier;

			bool result_1 = DrawRect(color, top); /* Top */
			bool result_2 = DrawRect(color, bottom); /* Bottom */
			bool result_3 = DrawRect(color, left); /* Left */
			bool result_4 = DrawRect(color, right); /* Right */
			return result_1 + result_2 + result_3 + result_4;
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
			DrawLine(line.color, line.pointA, line.pointB, line.world_space, line.parallax_multiplier);
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

		/* Draw a filled polygon and free the heap allocated point integer arrays */
		bool _DrawFilledPolygon(SDL_Renderer* renderer, Sint16* vx, Sint16* vy, int point_count, Uint32 color)
		{
			if (filledPolygonColor(renderer, vx, vy, point_count, color) == 0)
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

			return _DrawFilledPolygon(Global::RenderVars::Renderer, vx, vy, pointCount, uColor);
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

			return _DrawFilledPolygon(Global::RenderVars::Renderer, vx, vy, points.size(), uColor);
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
			bool success = DrawPolygon(color, intPoints, pointCount, world_space, parallax_multiplier);
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
			bool success = DrawPolygon(color, intPoints, points.size(), world_space, parallax_multiplier);
			delete[] intPoints;
			return success;
		}

		bool DrawPolygon(const Polygon& polygon)
		{
			return DrawPolygon(polygon.color, polygon.points, polygon.world_space);
		}
	}
}
