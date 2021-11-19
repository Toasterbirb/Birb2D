#pragma once
#include "../vendor/SDL2/SDL.h"
#include "../vendor/SDL2/SDL_ttf.h"
#include "../vendor/SDL2/SDL_image.h"
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_image.h>

#include "../include/Entity.hpp"
#include "../include/Font.hpp"


class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h, int p_refresh_rate);

	SDL_Texture* loadTexture(const char* p_filePath);
	TTF_Font* loadFont(const char* p_filePath, const int p_fontSize);

	void SetWindowSize(int width, int height);
	void ResetDrawColor();
	void DrawRect(SDL_Color color, Rect dimensions);

	Texture renderStaticTextTexture(const char* p_text, Font p_font);
	SDL_Texture* renderTextEntity(Entity& textEntity);

	int getRefreshRate();
	SDL_Renderer* getRenderer()
	{
		return renderer;
	}

	Vector2int getDimensions()
	{
		return windowDimensions;
	}


	void InitSDL();
	void QuitSDL();
	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void display();

	// Timestep -----------
	void timestepStart();
	bool timestepRunning();
	void timestepStep();
	void timestepEnd();
	float getTimestepAlpha();
	// --------------------
	
private:
	int refresh_rate;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Vector2int windowDimensions;

	// Timestep
	const float timeStep = 0.01f;
	float accumulator = 0.01f;
	float currentTime;
	int startTick;
};
