#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../include/Entity.hpp"
#include "../include/Font.hpp"

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	TTF_Font* loadFont(const char* p_filePath, const int p_fontSize);

	SDL_Texture* renderStaticText(const char* p_text, Font* p_font);
	SDL_Texture* renderTextEntity(Entity& textEntity);

	int getRefreshRate();
	SDL_Renderer* getRenderer()
	{
		return renderer;
	}

	Vector2f getDimensions()
	{
		return windowDimensions;
	}

	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Vector2f windowDimensions;
};
