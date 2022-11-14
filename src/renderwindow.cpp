#include "Renderwindow.hpp"
#include "Values.hpp"
#include "Logger.hpp"
#include "Diagnostics.hpp"
#include "Physics.hpp"
#include "microprofile.h"
#include <cstring>

#define PROFILER_GROUP "Rendering"
#define PROFILER_COLOR MP_LIGHTBLUE

namespace Birb
{
	static void DrawProgressBar(const Entity& entity);
	static void HandleAnimations(Entity* entity, SDL_Rect* src, SDL_Rect* dst);

	Window::Window()
	{
		InitSDL();
		InitSDL_image();
	}

	Window::Window(const std::string& p_title, const Vector2Int& p_window_dimensions, const int& p_refresh_rate, const bool& resizable)
	:win_title(p_title), refresh_rate(p_refresh_rate), dimensions(p_window_dimensions), original_window_dimensions(p_window_dimensions)
	{
#ifdef DEBUG
		Debug::Log("Creating window '" + win_title + "'...");
#endif

		/* Create a new window and initialize stuff for it */
		InitSDL();
		InitSDL_image();

		if (resizable)
			win = SDL_CreateWindow(p_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_window_dimensions.x, p_window_dimensions.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		else
			win = SDL_CreateWindow(p_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_window_dimensions.x, p_window_dimensions.y, SDL_WINDOW_SHOWN);

		if (win == NULL)
		{
			Debug::Log("Window failed to init: " + static_cast<std::string>(SDL_GetError()), Debug::error);
			exit(1);
		}

		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			Debug::Log("Renderer failed to init: " + static_cast<std::string>(SDL_GetError()), Debug::error);
			exit(1);
		}

		/* Set some global rendering variables */
		Global::RenderVars::RefreshRate 		= refresh_rate;
		Global::RenderVars::WindowDimensions 	= dimensions;
		Global::RenderVars::MainWindow 			= win;
		Global::RenderVars::Renderer 			= renderer;

		/* Define callback functions to some default values */
		OnWindowResize = DefaultOnWindowResize;

#ifdef DEBUG
		Debug::Log("Window '" + win_title + "' created successfully!");
#endif
	}

	Window::~Window()
	{
		Cleanup();
	}

	void Window::InitSDL()
	{
		/* Check if SDL has already been initialized */
		if (Global::IsInit::SDL)
			return;

#ifdef DEBUG
		if (Birb::Diagnostics::Debugging::InitMessages)
			Debug::Log("Initializing SDL...");
#endif

		if (SDL_Init(SDL_INIT_VIDEO) > 0)
		{
			Debug::Log("SDL Init failed: " + static_cast<std::string>(SDL_GetError()), Debug::error);
			exit(2);
		}
		else
		{
			Global::IsInit::SDL = true;
		}
	}

	void Window::InitSDL_image()
	{
		/* Check if SDL_image has already been initialized */
		if (Global::IsInit::SDL_image)
			return;

#ifdef DEBUG
		if (Birb::Diagnostics::Debugging::InitMessages)
			Debug::Log("Initializing SDL_image...");
#endif

		if (!(IMG_Init(IMG_INIT_PNG)))
		{
			Debug::Log("IMG_Init has failed" + static_cast<std::string>(SDL_GetError()), Debug::error);
			exit(2);
		}
		else
		{
			Global::IsInit::SDL_image = true;
		}
	}

	void Window::Cleanup()
	{
#ifdef DEBUG
		Debug::Log("Starting window cleanup for '" + win_title + "'...");
#endif /* DEBUG */
		SDL_DestroyWindow(win);

		/* FIXME: There's some sort of memory leak with SDL_Renderer. Destroying the renderer
		 * causes heck of a lot of valgrind errors
		 * Ref: https://stackoverflow.com/questions/20823886/sdl2-memory-leaks-on-sdl-destroyrenderer
		 *
		 * Also, this deconstructor is getting called twice in some cases for some weird reason */

		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
		SDL_DestroyRenderer(renderer);

		/* Also de-initialize SDL_Mixer if audio has been used */
		if (Global::IsInit::SDL_mixer)
		{
			Mix_Quit();
			Global::IsInit::SDL_mixer = false;
		}

		Global::IsInit::SDL = false;
		Global::IsInit::SDL_image = false;
		Global::IsInit::SDL_ttf = false;

		Global::RenderVars::MainWindow = NULL;
		Global::RenderVars::Renderer = NULL;

#ifdef DEBUG
		Debug::Log("Window '" + win_title + "' destroyed!");
#endif /* DEBUG */
	}

	void Window::Clear()
	{
		/* Clear the window renderer. Call before rendering stuff */
		SDL_RenderClear(Global::RenderVars::Renderer);
	}

	void Window::Display()
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Window display", PROFILER_COLOR);
		SDL_RenderPresent(Global::RenderVars::Renderer);
		MicroProfileFlip(nullptr);
	}

	Vector2Int Window::CursorPosition() const
	{
		Vector2Int pos;
		SDL_GetMouseState(&pos.x, &pos.y);
		return pos;
	}

	bool Window::CursorInRect(const Rect& rect) const
	{
		Vector2Int cursorPos = CursorPosition();

		if (cursorPos.x > rect.x && cursorPos.x < rect.x + rect.w)
			if (cursorPos.y > rect.y && cursorPos.y < rect.y + rect.h)
				return true;

		return false;
	}

	void Window::SetWindowSize(const Vector2Int& dimensions)
	{
		SDL_SetWindowSize(win, dimensions.x, dimensions.y);
		this->dimensions = dimensions;
	}

	Vector2 Window::window_dimensions_multiplier()
	{
		return Vector2(static_cast<float>(dimensions.x) / static_cast<float>(original_window_dimensions.x),
						static_cast<float>(dimensions.y) / static_cast<float>(original_window_dimensions.y));
	}

	bool Window::PollEvents()
	{
		return (SDL_PollEvent(&event) != 0);
	}

	void Window::EventTick(const SDL_Event& event, bool* GameRunning)
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Window event tick", PROFILER_COLOR);
		switch (event.type)
		{
			/* Handle window resizing */
			case (SDL_WINDOWEVENT):
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					SetWindowSize(Vector2Int(event.window.data1, event.window.data2));
					OnWindowResize(*this);
					Global::RenderVars::WindowDimensions = dimensions;
				}
				break;

			case (SDL_QUIT):
				Debug::Log("Quitting...");
				*GameRunning = false;
				break;

			default:
				break;
		}
	}

	Input::KeyCode Window::key_event() const
	{
		return Input::EventToKeycode(this->event);
	}

	bool Window::isKeyDown() const
	{
		return (this->event.type == SDL_KEYDOWN);
	}

	bool Window::isKeyUp() const
	{
		return (this->event.type == SDL_KEYUP);
	}

	bool Window::isMouseDown() const
	{
		return (this->event.type == SDL_MOUSEBUTTONDOWN);
	}

	bool Window::isMouseUp() const
	{
		return (this->event.type == SDL_MOUSEBUTTONUP);
	}

	void Window::DefaultOnWindowResize(Window& window)
	{
		return;
	}

	void HandleAnimations(Entity* entity, SDL_Rect* src, SDL_Rect* dst)
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Handle animations", PROFILER_COLOR);
		Vector2Int atlasPos = entity->getAtlasPosition(entity->animationComponent.frameIndex);
		src->x = atlasPos.x;
		src->y = atlasPos.y;
		src->w = entity->animationComponent.spriteSize.x;
		src->h = entity->animationComponent.spriteSize.y;

		dst->x = entity->rect.x - (Global::RenderVars::CameraPosition.x * entity->world_space);
		dst->y = entity->rect.y - (Global::RenderVars::CameraPosition.y * entity->world_space);
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

	void DrawProgressBar(const Entity& entity)
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw progress bar", PROFILER_COLOR);
		/* Draw progress bar background unless the bar is full */
		if (entity.progressBarComponent.value < entity.progressBarComponent.maxValue)
			Render::DrawRect(*entity.progressBarComponent.backgroundColor, entity.rect);

		/* Draw the progress bar filler box */
		Birb::Rect fillRect(entity.rect.x, entity.rect.y, (entity.progressBarComponent.value / entity.progressBarComponent.maxValue) * entity.rect.w, entity.rect.h);
		Render::DrawRect(*entity.progressBarComponent.fillColor, fillRect);

		/* Draw the progress bar outer box */
		Render::DrawRect(*entity.progressBarComponent.borderColor, entity.rect, entity.progressBarComponent.borderWidth);
	}

	bool Render::DrawEntity(Entity& entity)
	{
		MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw entity", PROFILER_COLOR);
		if (!entity.active)
			return true;

		/* Check if the sprite would be even visible */
		if (entity.rect.w <= 0 || entity.rect.h <= 0)
		{
			Birb::Debug::Log("Tried to render an entity with size of <= 0", Debug::Type::warning);
			return false;
		}

		SDL_Rect src;
		SDL_Rect dst;
		Vector2Int centerPoint;

		/* Get texture data */
		int texWidth 	= 0;
		int texHeight 	= 0;

		/* Skip the texture width tests if the entity doesn't have a texture on it */
		if (entity.sprite.isLoaded())
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Entity sprite scale calculation", PROFILER_COLOR);
			texWidth 	= entity.sprite.dimensions().x;
			texHeight 	= entity.sprite.dimensions().y;

			if (texWidth <= 0 || texHeight <= 0)
			{
				Birb::Debug::Log("Tried to render an entity with a texture with size of <= 0", Debug::Type::warning);
				return false;
			}

			if (entity.animationComponent.frameCount <= 0) /* Check if the entity has animations */
			{
				src.x = 0;
				src.y = 0;
				src.w = texWidth;
				src.h = texHeight;

				dst.x = entity.rect.x - (Global::RenderVars::CameraPosition.x * entity.world_space);
				dst.y = entity.rect.y - (Global::RenderVars::CameraPosition.y * entity.world_space);
				dst.w = entity.rect.w * entity.localScale.x;
				dst.h = entity.rect.h * entity.localScale.y;
			}
			else
			{
				/* Entity probably has an animation component */
				HandleAnimations(&entity, &src, &dst);
			}
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

			/* We are done if there isn't going to be a sprite to render */
			if (!entity.sprite.isLoaded())
				return true;
		}

		/* Skip rendering the texture if one doesn't exist on the entity */
		if (entity.sprite.isLoaded())
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw entity sprite", PROFILER_COLOR);
			centerPoint = Vector2Int((entity.rect.w * entity.localScale.x) / 2, (entity.rect.h * entity.localScale.y) / 2);
			SDL_Point center = { centerPoint.x, centerPoint.y };

			if (SDL_RenderCopyEx(Global::RenderVars::Renderer, entity.sprite.sdlTexture(), &src, &dst, entity.angle, &center, SDL_FLIP_NONE) < 0)
				Debug::Log("Error rendering [" + entity.name + ", (" + entity.rect.toString() + ")]. SDL Error: " + SDL_GetError(), Debug::error);
			else
				return true;
		}

		/* If nothing was rendered so far, simply render the rect */
		DrawRect(entity.rect.color, entity.rect);

		return true;
	}

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
			rectangle.x -= (Global::RenderVars::CameraPosition.x * dimensions.world_space);
			rectangle.y -= (Global::RenderVars::CameraPosition.y * dimensions.world_space);
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

		void DrawLine(const Color& color, const Vector2Int& pointA, const Vector2Int& pointB, const bool& world_space)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw line (int)", PROFILER_COLOR);
			SetRenderDrawColor(color);
			SDL_RenderDrawLine(Global::RenderVars::Renderer,
					pointA.x - (Global::RenderVars::CameraPosition.x * world_space),
					pointA.y - (Global::RenderVars::CameraPosition.y * world_space),
					pointB.x - (Global::RenderVars::CameraPosition.x * world_space),
					pointB.y - (Global::RenderVars::CameraPosition.y * world_space));
			ResetDrawColor();
		}

		void DrawLine(const Color& color, const Vector2& pointA, const Vector2& pointB, const bool& world_space)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw line (float)", PROFILER_COLOR);
			SetRenderDrawColor(color);
			SDL_RenderDrawLineF(Global::RenderVars::Renderer,
					pointA.x - (Global::RenderVars::CameraPosition.x * world_space),
					pointA.y - (Global::RenderVars::CameraPosition.y * world_space),
					pointB.x - (Global::RenderVars::CameraPosition.x * world_space),
					pointB.y - (Global::RenderVars::CameraPosition.y * world_space));
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

		void DrawLines(const Color& color, Vector2Int* points, const int& pointCount, const bool& world_space)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw multiple lines", PROFILER_COLOR);
			SDL_Point* sdlPoints = new SDL_Point[pointCount];
			for (int i = 0; i < pointCount; ++i)
			{
				sdlPoints[i] = {
					points[i].x - static_cast<int>(Global::RenderVars::CameraPosition.x * world_space),
					points[i].y - static_cast<int>(Global::RenderVars::CameraPosition.y * world_space)
				};
			}

			SetRenderDrawColor(color);
			SDL_RenderDrawLines(Global::RenderVars::Renderer, sdlPoints, pointCount);
			delete[] sdlPoints;
			ResetDrawColor();
		}

		void DrawLines(const Color& color, Vector2* points, const int& pointCount, const bool& world_space)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw multiple lines", PROFILER_COLOR);
			SDL_FPoint* sdlPoints = new SDL_FPoint[pointCount];
			for (int i = 0; i < pointCount; ++i)
			{
				sdlPoints[i] = {
					points[i].x - (Global::RenderVars::CameraPosition.x * world_space),
					points[i].y - (Global::RenderVars::CameraPosition.y * world_space)
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

		bool DrawCircle(const Color& color, const Vector2Int& pos, const int& radius, const bool& world_space)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw multiple lines", PROFILER_COLOR);
			Uint32 uColor = (255<<24) + (int(color.b)<<16) + (int(color.g)<<8) + int(color.r);;
			if (filledCircleColor(Global::RenderVars::Renderer,
						pos.x - (Global::RenderVars::CameraPosition.x * world_space),
						pos.y - (Global::RenderVars::CameraPosition.y * world_space),
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

		bool DrawPolygon(const Color& color, Vector2Int* points, const int& pointCount, const bool& world_space)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw polygon", PROFILER_COLOR);
			Uint32 uColor = (255<<24) + (int(color.b)<<16) + (int(color.g)<<8) + int(color.r);;

			/* Convert Vector2Int points into Sint16 vectors and add the camera offset */
			Sint16* vx = new Sint16[pointCount];
			Sint16* vy = new Sint16[pointCount];
			for (int i = 0; i < pointCount; ++i)
			{
				vx[i] = points[i].x - (Global::RenderVars::CameraPosition.x * world_space);
				vy[i] = points[i].y - (Global::RenderVars::CameraPosition.y * world_space);
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

		bool DrawPolygon(const Color& color, const std::vector<Vector2Int>& points, const bool& world_space)
		{
			MICROPROFILE_SCOPEI(PROFILER_GROUP, "Draw polygon", PROFILER_COLOR);
			Uint32 uColor = (255<<24) + (int(color.b)<<16) + (int(color.g)<<8) + int(color.r);;

			/* Convert Vector2Int points into Sint16 vectors and add the camera offset */
			Sint16* vx = new Sint16[points.size()];
			Sint16* vy = new Sint16[points.size()];
			for (size_t i = 0; i < points.size(); ++i)
			{
				vx[i] = points[i].x - (Global::RenderVars::CameraPosition.x * world_space);
				vy[i] = points[i].y - (Global::RenderVars::CameraPosition.y * world_space);
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
		bool DrawPolygon(const Color& color, Vector2* points, const int& pointCount, const bool& world_space)
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

		bool DrawPolygon(const Color& color, const std::vector<Vector2>& points, const bool& world_space)
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
