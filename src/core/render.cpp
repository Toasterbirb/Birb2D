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
		void HandleAnimations(Entity* entity, SDL_Rect* src, SDL_Rect* dst)
		{
			Vector2int atlasPos = entity->getAtlasPosition(entity->animationComponent.frameIndex);
			src->x = atlasPos.x;
			src->y = atlasPos.y;
			src->w = entity->animationComponent.spriteSize.x;
			src->h = entity->animationComponent.spriteSize.y;

			dst->x = entity->rect.x;
			dst->y = entity->rect.y;
			dst->w = src->w * entity->localScale.x;
			dst->h = src->h * entity->localScale.y;



			/* Set the current atlas position to the next frame */
			if (entity->animationComponent.animationQueued || entity->animationComponent.loop)
			{
				if (entity->animationComponent.frameTimer.running && entity->animationComponent.frameTimer.ElapsedSeconds() >= (1.0 / entity->animationComponent.fps))
				{
					if (entity->animationComponent.frameIndex < entity->animationComponent.lastFrame)
					{
						entity->animationComponent.frameIndex++;
						entity->animationComponent.frameTimer.Start();
					}
				}
				else if (!entity->animationComponent.frameTimer.running)
				{
					/* Start the frame timer */
					entity->animationComponent.frameTimer.Start();
				}

				if (entity->animationComponent.loop && entity->animationComponent.frameIndex >= entity->animationComponent.lastFrame)
				{
					entity->animationComponent.frameIndex = 0;
				}
				else if (entity->animationComponent.animationQueued && entity->animationComponent.frameIndex >= entity->animationComponent.lastFrame)
				{
					entity->animationComponent.frameIndex = entity->animationComponent.lastFrame;
					entity->animationComponent.animationQueued = false;
				}
			}
		}
#endif /* LIB_SDL */

		void DrawProgressBar(const Entity& entity)
		{
			/* Draw progress bar background unless the bar is full */
			if (entity.progressBarComponent.value < entity.progressBarComponent.maxValue)
				Render::DrawRect(*entity.progressBarComponent.backgroundColor, entity.rect);

			/* Draw the progress bar filler box */
			Birb::Rect fillRect(entity.rect.x, entity.rect.y, (entity.progressBarComponent.value / entity.progressBarComponent.maxValue) * entity.rect.w, entity.rect.h);
			Render::DrawRect(*entity.progressBarComponent.fillColor, fillRect);

			/* Draw the progress bar outer box */
			Render::DrawRect(*entity.progressBarComponent.borderColor, entity.rect, entity.progressBarComponent.borderWidth);
		}

		bool DrawEntity(Entity& entity)
		{
			if (!entity.active)
				return true;

			//if (entity.sprite == nullptr)
			//{
			//	Debug::Log("Entity '" + entity.name + "' has no sprite to render", Debug::error);
			//	return false;
			//}

			/* Check if the sprite would be even visible */
			if (entity.rect.w <= 0 || entity.rect.h <= 0)
			{
				Birb::Debug::Log("Tried to render an entity with size of <= 0", Debug::Type::warning);
				return false;
			}

#ifdef LIB_SDL
			SDL_Rect src;
			SDL_Rect dst;
#else
			Rect src;
			Rect dst;
#endif /* LIB_SDL */
			Vector2int centerPoint;

			/* Get texture data */
			int texWidth 	= 0;
			int texHeight 	= 0;

			/* Skip the texture width tests if the entity doesn't have a texture on it */
			if (entity.sprite.isLoaded())
			{
				texWidth 	= entity.sprite.dimensions().x;
				texHeight 	= entity.sprite.dimensions().y;

				if (texWidth <= 0 || texHeight <= 0)
				{
					Birb::Debug::Log("Tried to render an entity with a texture with size of <= 0", Debug::Type::warning);
					return false;
				}
			}

			if (entity.animationComponent.frameCount <= 0) /* Check if the entity has animations */
			{
				src.x = 0;
				src.y = 0;
				src.w = texWidth;
				src.h = texHeight;

				dst.x = entity.rect.x;
				dst.y = entity.rect.y;
				dst.w = entity.rect.w * entity.localScale.x;
				dst.h = entity.rect.h * entity.localScale.y;
			}
			else
			{
				/* Entity probably has an animation component */
#ifdef LIB_SDL
				HandleAnimations(&entity, &src, &dst);
#else
				// TODO: Figure out how to do animations without SDL
#endif /* LIB_SDL */
			}

			/* Check if the entity has an active progress bar component */
			if (entity.progressBarComponent.active)
			{
				/* Crop the sprite if the value of a the progress bar component is less than its max value */
				if (entity.progressBarComponent.value < entity.progressBarComponent.maxValue)
				{
					dst.x = dst.x + entity.progressBarComponent.borderWidth;
					src.w = (entity.progressBarComponent.value / entity.progressBarComponent.maxValue) * texWidth - (entity.progressBarComponent.borderWidth * 2);
				}

				DrawProgressBar(entity);
			}

			centerPoint = Vector2int((entity.rect.w * entity.localScale.x) / 2, (entity.rect.h * entity.localScale.y) / 2);

			// TODO: Figure out rendering without SDL
#ifdef LIB_SDL
			SDL_Point center = { centerPoint.x, centerPoint.y };

			/* Skip rendering the texture if one doesn't exist on the entity */
			if (entity.sprite.isLoaded() == true)
			{
				if (SDL_RenderCopyEx(Global::RenderVars::Renderer, entity.sprite.sdlTexture(), &src, &dst, entity.angle, &center, SDL_FLIP_NONE) < 0)
					Debug::Log("Error rendering [" + entity.name + ", (" + entity.rect.toString() + ")]. SDL Error: " + SDL_GetError(), Debug::error);
				else
					return true;
			}
#endif /* LIB_SDL */

			return true;
		}


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
