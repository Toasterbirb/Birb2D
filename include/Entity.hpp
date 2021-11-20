#pragma once

#ifndef PLATFORM_WIN
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#else
#include "../vendor/SDL2_win/SDL2/x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../vendor/SDL2_win/SDL2_ttf-2.0.15/x86_64-w64-mingw32/include/SDL2/SDL_ttf.h"
#include "../vendor/SDL2_win/SDL2_image-2.0.5/x86_64-w64-mingw32/include/SDL2/SDL_image.h"
#endif



#include "../include/Math.hpp"
#include "../include/Font.hpp"
#include "../include/Utils.hpp"

//SDL_Texture* renderStaticText(const char* p_text, Font* p_font);

namespace Birb2D
{
	class Entity
	{
	public:
		// Normal texture entities
		Entity();
		Entity(const char* p_name, Vector2f p_pos, Vector2f p_dimensions, Texture p_tex);
		Entity(const char* p_name, Vector2f p_pos, Vector2f p_dimensions, float p_angle, Texture p_tex);

		// Scalable texture entities
		Entity(const char* p_name, Vector2f p_pos, float p_scaleMultiplier, Vector2f p_dimensions, Texture p_tex);
		Entity(const char* p_name, Vector2f p_pos, float p_scaleMultiplier, Vector2f p_dimensions, float p_angle, SDL_Texture* p_tex);

		// Text entities
		Entity(const char* p_name, std::string p_text, Vector2f p_pos, Birb2D::Font p_font);
		Entity(const char* p_name, std::string p_text, Vector2f p_pos, Birb2D::Font p_font, SDL_Texture* p_tex, float p_angle);

		Vector2f& getPos();
		void setPos(Vector2f p_pos);
		Rect* getRect();

		float& getAngle();
		void setAngle(float p_angle);

		Birb2D::Font getFont();

		std::string getText();

		std::string getName();

		void updateText(std::string p_text, SDL_Texture* p_tex);
		//void setText(std::string p_text);
		//void setTexture(SDL_Texture* p_tex);
		
		float getLocalScale()
		{
			return localScale;
		}
		

		SDL_Texture* getTex();
		Rect getCurrentFrame();
	private:
		std::string name;
		Vector2f pos;
		Rect pos_rect;
		float localScale = 1.00f;
		float angle;

		// Text entity vars
		std::string text;
		Birb2D::Font font;

		Rect currentFrame;
		SDL_Texture* tex;
	};
}
