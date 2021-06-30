#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


#include "../include/Math.hpp"
#include "../include/Font.hpp"

//SDL_Texture* renderStaticText(const char* p_text, Font* p_font);

class Entity
{
public:
	// Normal texture entities
	Entity(const char* p_name, Vector2f p_pos, Vector2f p_dimensions, SDL_Texture* p_tex);
	Entity(const char* p_name, Vector2f p_pos, Vector2f p_dimensions, float p_angle, SDL_Texture* p_tex);

	// Scalable texture entities
	Entity(const char* p_name, Vector2f p_pos, float p_scaleMultiplier, Vector2f p_dimensions, SDL_Texture* p_tex);
	Entity(const char* p_name, Vector2f p_pos, float p_scaleMultiplier, Vector2f p_dimensions, float p_angle, SDL_Texture* p_tex);

	// Text entities
	Entity(const char* p_name, std::string p_text, Vector2f p_pos, Font* p_font);
	Entity(const char* p_name, std::string p_text, Vector2f p_pos, Font* p_font, SDL_Texture* p_tex, float p_angle);

	Vector2f& getPos();
	void setPos(Vector2f p_pos);
	SDL_Rect* getRect();

	float& getAngle();
	void setAngle(float p_angle);

	Font* getFont();

	std::string getText();

	std::string getName();

	void updateText(std::string p_text, SDL_Texture* p_tex);
	//void setText(std::string p_text);
	//void setTexture(SDL_Texture* p_tex);

	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
private:
	std::string name;
	Vector2f pos;
	SDL_Rect pos_rect;
	float angle;

	// Text entity vars
	std::string text;
	Font* font;

	SDL_Rect currentFrame;
	SDL_Texture* tex;
};
