#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Utils.hpp"
#include "Entity.hpp"

namespace Birb
{
	struct Window
	{
		Window();
		Window(std::string p_title, Vector2int p_window_dimensions, int p_refresh_rate, bool resizable);

		/* -- Init stuff functions -- */
		static void InitSDL();
		static void InitSDL_ttf();
		static void InitSDL_image();
		/* -------------------------- */

		/* -- Rendering and cleanup functions -- */
		void Clear();
		void Display();
		void Cleanup();
		/* ------------------------------------- */

		/* -- Cursor functions -- */
		Vector2int CursorPosition();
		bool CursorInRect(Rect rect);
		/* ---------------------- */

		/* -- Basic window events -- */
		void SetWindowSize(Vector2int dimensions);
		void EventTick(SDL_Event event, bool* GameRunning);
		bool PollEvents();
		SDL_Event event;
		/* ------------------------- */

		/* -- Window variables -- */
		std::string win_title;
		int refresh_rate;
		SDL_Window* win;
		SDL_Renderer* renderer = NULL;
		Vector2int window_dimensions;
		Vector2int original_window_dimensions;
		Vector2f window_dimensions_multiplier; ///< Contains the difference between the current and old window dimensions. DO NOT MODIFY!
		/* ---------------------- */
	};

	/// Methods for loading different resources like fonts and textures
	struct Resources
	{
		static SDL_Texture* LoadTexture(std::string p_filePath);
		static SDL_Texture* TextSprite(std::string text, TTF_Font* font, SDL_Color& color);
		static SDL_Texture* TextSprite(std::string text, TTF_Font* font, SDL_Color& color, SDL_Color& bgColor);
		static TTF_Font* 	LoadFont(std::string p_filePath, int p_fontSize);
		static Uint8* 		CopyTexturePixels(SDL_Surface* surface, int* width, int* height, int* pitch);
	};

	/// Methods for rendering things
	struct Render
	{
		static void DrawEntity(Entity& entity);
		static void ResetDrawColor();
		static void DrawRect(SDL_Color color, Rect dimensions); 			///< Draw filled rect
		static void DrawRect(SDL_Color color, Rect dimensions, int width); 	///< Draw hollow rect
		static void DrawLine(SDL_Color color, Vector2int pointA, Vector2int pointB);
		static void DrawCircle(SDL_Color color, Vector2int pos, int radius);
		static void SetRenderDrawColor(SDL_Color color);
	};
}
