#include "Renderwindow.hpp"
#include "Values.hpp"
#include "Logger.hpp"

namespace Birb2D
{
	Window::Window(std::string p_title, Vector2int p_window_dimensions, int p_refresh_rate)
	:refresh_rate(p_refresh_rate), window_dimensions(p_window_dimensions), win_title(p_title)
	{
		/* Create a new window and initialize stuff for it */
		InitSDL();
		InitSDL_ttf();
		InitSDL_image();

		win = SDL_CreateWindow(p_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_window_dimensions.x, p_window_dimensions.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

		if (win == NULL)
			Debug::Log("Window failed to init: " + (std::string)SDL_GetError(), Debug::error);

		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

		/* Set some global rendering variables */
		Global::RenderVars::RefreshRate = p_refresh_rate;
		Global::RenderVars::MainWindow 	= win;
		Global::RenderVars::Renderer 	= renderer;
	}

	void Window::InitSDL()
	{
		/* Check if SDL has already been initialized */
		if (Global::IsInit::SDL)
			return;

		Debug::Log("Initializing SDL...");
		if (SDL_Init(SDL_INIT_VIDEO) > 0)
		{
			Debug::Log("SDL Init failed: " + (std::string)SDL_GetError(), Debug::error);
			exit(2);
		}
		else
		{
			Global::IsInit::SDL = true;
		}
	}

	void Window::InitSDL_ttf()
	{
		/* Check if SDL_ttf has already been initialized */
		if (Global::IsInit::SDL_ttf)
			return;

		Debug::Log("Initializing SDL_ttf...");
		if (TTF_Init() == -1)
		{
			Debug::Log("TTF_Init has failed: " + (std::string)TTF_GetError(), Debug::error);
			exit(2);
		}
		else
		{
			Global::IsInit::SDL_ttf = true;
		}
	}

	void Window::InitSDL_image()
	{
		/* Check if SDL_image has already been initialized */
		if (Global::IsInit::SDL_image)
			return;

		Debug::Log("Initializing SDL_image...");
		if (!(IMG_Init(IMG_INIT_PNG)))
		{
			Debug::Log("IMG_Init has failed" + (std::string)SDL_GetError(), Debug::error);
			exit(2);
		}
		else
		{
			Global::IsInit::SDL_image = true;
		}
	}

	void Window::Cleanup()
	{
		Global::IsInit::SDL = false;
		Global::IsInit::SDL_image = false;

		Debug::Log("Destroying the window");
		SDL_DestroyWindow(win);
	}

	void Window::Clear()
	{
		/* Clear the window renderer. Call before rendering stuff */
		SDL_RenderClear(Global::RenderVars::Renderer);
	}

	void Window::Display()
	{
		SDL_RenderPresent(Global::RenderVars::Renderer);
	}

	void Window::SetWindowSize(Vector2int dimensions)
	{
		SDL_SetWindowSize(win, dimensions.x, dimensions.y);
		window_dimensions = dimensions;
	}

	void Window::EventTick(SDL_Event event, bool* GameRunning)
	{
		switch (event.type)
		{
			/* Handle window resizing */
			case (SDL_WINDOWEVENT):
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
					SetWindowSize(Vector2int(event.window.data1, event.window.data2));
				break;
			
			case (SDL_QUIT):
				Debug::Log("Quitting...");
				*GameRunning = false;
				break;
			
			default:
				break;
		}
	}

	SDL_Texture* Resources::LoadTexture(std::string p_filePath)
	{
		SDL_Texture* texture = NULL;
		texture = IMG_LoadTexture(Global::RenderVars::Renderer, p_filePath.c_str());
		
		if (texture == NULL)
			Debug::Log("Failed to load texture [" + p_filePath + "]: " + (std::string)SDL_GetError(), Debug::error);

		return texture;
	}

	TTF_Font* Resources::LoadFont(std::string p_filePath, int p_fontSize)
	{
		TTF_Font* font;
		font = TTF_OpenFont(p_filePath.c_str(), p_fontSize);

		if (!font)
		{
			Debug::Log("Error while loading font [" + p_filePath + "] TTF_Error: " + (std::string)TTF_GetError(), Debug::error);
		}

		return font;
	}

	SDL_Texture* Resources::TextSprite(std::string text, TTF_Font* font, SDL_Color& color)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
		if (surface == nullptr)
			Debug::Log("Error creating SDL_Surface. Text: " + (std::string)text + ". SDL Error: " + (std::string)SDL_GetError(), Debug::error);

		SDL_Texture* texture = SDL_CreateTextureFromSurface(Global::RenderVars::Renderer, surface);
		if (texture == nullptr)
			Debug::Log("Error creating texture from surface: " + (std::string)SDL_GetError(), Debug::error);

		SDL_FreeSurface(surface);
		return texture;
	}

	void Render::DrawEntity(Entity& entity)
	{
		if (entity.sprite == nullptr)
		{
			Debug::Log("Entity '" + entity.name + "' has no sprite to render", Debug::error);
			return;
		}

		SDL_Rect src;
		SDL_Rect dst;
		Vector2int centerPoint;

		/* Get texture data */
		int texWidth;
		int texHeight;
		SDL_QueryTexture(entity.sprite, NULL, NULL, &texWidth, &texHeight);

		src.x = 0;
		src.y = 0;
		src.w = texWidth;
		src.h = texHeight;

		dst.x = entity.rect.x;
		dst.y = entity.rect.y;
		dst.w = entity.rect.w * entity.localScale.x;
		dst.h = entity.rect.h * entity.localScale.y;

		centerPoint = Vector2int(entity.rect.w / 2, entity.rect.h / 2);
		SDL_Point center = { centerPoint.x, centerPoint.y };
		//Debug::Log("Angle: " + std::to_string(entity.angle));

		if (SDL_RenderCopyEx(Global::RenderVars::Renderer, entity.sprite, &src, &dst, entity.angle, &center, SDL_FLIP_NONE) < 0)
			Debug::Log("Error rendering [" + entity.name + "]. Error: " + SDL_GetError(), Debug::error);
	}

	void Render::ResetDrawColor()
	{
		SDL_SetRenderDrawColor(Global::RenderVars::Renderer, 0, 0, 0, 255);
	}

	void Render::DrawRect(SDL_Color color, Rect dimensions)
	{
		SDL_SetRenderDrawColor(Global::RenderVars::Renderer, color.r, color.g, color.b, color.a);
		SDL_Rect rectangle = dimensions.getSDLRect();
		SDL_RenderFillRect(Global::RenderVars::Renderer, &rectangle);
		ResetDrawColor();
	}

	void Render::DrawCircle(SDL_Color color, Vector2int pos, int radius)
	{
		//SDL_SetRenderDrawColor(Global::RenderVars::Renderer, color.r, color.g, color.b, color.a);
		Uint32 uColor = (255<<24) + (int(color.b)<<16) + (int(color.g)<<8) + int(color.r);;
		filledCircleColor(Global::RenderVars::Renderer, pos.x, pos.y, radius, uColor);
		ResetDrawColor();
	}
}
