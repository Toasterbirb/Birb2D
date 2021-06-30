#include <SDL2/SDL_render.h>
#include <iostream>

#include "../include/RenderWindow.hpp"
#include "../include/Entity.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h,
			SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init: " << SDL_GetError() << "\n";
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	windowDimensions.x = p_w;
	windowDimensions.y = p_h;
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture: " << SDL_GetError() << "\n";

	return texture;
}

TTF_Font* RenderWindow::loadFont(const char* p_filePath, const int p_fontSize)
{
	// Load up a font
	TTF_Font* font;
	font = TTF_OpenFont(p_filePath, p_fontSize);
	if (!font)
	{
		std::cout << "Error while loading font [" << p_filePath << "]: " << TTF_GetError() << std::endl;
		exit(1);
	}

	return font;
}

SDL_Texture* RenderWindow::renderStaticText(const char* p_text, Font* p_font)
{
	SDL_Surface* surface = TTF_RenderText_Blended(p_font->getTTFFont(), p_text, p_font->getColor());
	if (surface == nullptr)
	{
		std::cout << "Error creating SDL_Surface: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr)
	{
		std::cout << "Error creating texture from surface: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	SDL_FreeSurface(surface);
	return texture;
}

SDL_Texture* RenderWindow::renderTextEntity(Entity& textEntity)
{
	SDL_Surface* surface = TTF_RenderText_Blended(textEntity.getFont()->getTTFFont(), textEntity.getText().c_str(), textEntity.getFont()->getColor());

	if (surface == nullptr)
	{
		std::cout << "Error creating SDL_Surface: " << SDL_GetError() << ". Entity: " << textEntity.getName() << ". Text: [" << textEntity.getText() << "]" << std::endl;
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr)
	{
		std::cout << "Error creating texture from surface: " << SDL_GetError() << ". Entity: " << textEntity.getName() << ". Text: [" << textEntity.getText() << "]" << std::endl;
		return nullptr;
	}

	SDL_FreeSurface(surface);
	return texture;
}

int RenderWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex( window );

	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);

	return mode.refresh_rate;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getPos().x;
	dst.y = p_entity.getPos().y;
	dst.w = p_entity.getCurrentFrame().w;
	dst.h = p_entity.getCurrentFrame().h;

	if (dst.w == 0 || dst.h == 0)
	{
		std::cout << "ERROR! Texture with size of 0 in entity " << p_entity.getName() << std::endl;
		return;
	}

	SDL_Point center = {p_entity.getCurrentFrame().w / 2,p_entity.getCurrentFrame().h / 2};

	if (SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, p_entity.getAngle(), &center, SDL_FLIP_NONE) < 0)
	{
		std::cout << "Error during rendering: " << SDL_GetError() << ". Entity: " << p_entity.getName() << std::endl;
	}
	//SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}
