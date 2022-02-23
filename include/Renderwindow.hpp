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
		Window(const std::string& p_title, const Vector2int& p_window_dimensions, const int& p_refresh_rate, const bool& resizable);

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
		bool CursorInRect(const Rect& rect);
		/* ---------------------- */

		/* -- Basic window events -- */
		void SetWindowSize(const Vector2int& dimensions);
		void EventTick(const SDL_Event& event, bool* GameRunning);
		bool PollEvents(); ///< Runs SDL_PollEvent and saves the result to the *event* variable
		SDL_Event event;
		/* ------------------------- */

		/* -- Window variables -- */
		std::string win_title; ///< Window title text
		int refresh_rate; ///< Window refreshrate. Can be changed during runtime if needed for some reason
		SDL_Window* win;
		SDL_Renderer* renderer = NULL;
		Vector2int window_dimensions; ///< Current window dimensions
		Vector2int original_window_dimensions; ///< Window dimensions on application startup before its modified by the user
		Vector2f window_dimensions_multiplier; ///< Contains the difference between the current and old window dimensions. DO NOT MODIFY!
		/* ---------------------- */
	};

	/// Methods for loading different resources like fonts and textures
	struct Resources
	{
		static SDL_Texture* LoadTexture(const std::string& p_filePath);
		static SDL_Texture* TextSprite(const std::string& text, TTF_Font* font, const SDL_Color& color);
		static SDL_Texture* TextSprite(const std::string& text, TTF_Font* font, const SDL_Color& color, const SDL_Color& bgColor);
		static TTF_Font* 	LoadFont(const std::string& p_filePath, const int& p_fontSize);
		static Uint8* 		CopyTexturePixels(SDL_Surface* surface, int* width, int* height, int* pitch);
	};

	/// Methods for rendering things
	struct Render
	{
		static bool DrawEntity(Entity& entity);
		static void ResetDrawColor();
		static void DrawRect(const SDL_Color& color, const Rect& dimensions); ///< Draw filled rect
		static void DrawRect(const SDL_Color& color, const Rect& dimensions, const int& width); ///< Draw hollow rect
		static void DrawLine(const SDL_Color& color, const Vector2int& pointA, const Vector2int& pointB);
		static void DrawCircle(const SDL_Color& color, const Vector2int& pos, const int& radius);
		static void SetRenderDrawColor(const SDL_Color& color);
	};
}
