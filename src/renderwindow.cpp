//#include <SDL2/SDL_render.h>
#include <iostream>

#include "../include/RenderWindow.hpp"
#include "../include/Audio.hpp"
#include "../include/Entity.hpp"
#include "../include/Widgets.hpp"

Birb2D::RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h, int p_refresh_rate)
:window(NULL), renderer(NULL), refresh_rate(p_refresh_rate)
{
	// INIT SDL STUFF
	// Remember to call cleanUp function when closing the window
	// You will have to call SDL_Quit() separately when closing the game

	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL INIT FAILED: " << SDL_GetError() << "\n";

	// Init SDL_image
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << "\n";

	// Init SDL_ttf
	if (TTF_Init() == -1) {
		std::cout << "TTF_Init has failed. Error: " << TTF_GetError() << "\n";
    	exit(2);
	}

	// Init SDL_mixer
	Audio audio;
	audio.initAudio(MIX_INIT_MP3);


	window = SDL_CreateWindow(p_title,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			p_w, p_h,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (window == NULL)
	{
		std::cout << "Window failed to init: " << SDL_GetError() << "\n";
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	windowDimensions.x = p_w;
	windowDimensions.y = p_h;

	// Init timestep
	currentTime = utils::hireTimeInSeconds();
}

SDL_Texture* Birb2D::RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture: " << SDL_GetError() << "\n";

	return texture;
}

TTF_Font* Birb2D::RenderWindow::loadFont(const char* p_filePath, const int p_fontSize)
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

void Birb2D::RenderWindow::SetWindowSize(int width, int height)
{
	SDL_SetWindowSize(window, width, height);
	Vector2int newDimensions(width, height);
	windowDimensions = newDimensions;
}

void Birb2D::RenderWindow::ResetDrawColor()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Birb2D::RenderWindow::DrawRect(SDL_Color color, Rect dimensions)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rectangle = dimensions.getSDLRect();
	SDL_RenderFillRect(renderer, &rectangle);
	ResetDrawColor();
}

Birb2D::Texture Birb2D::RenderWindow::renderStaticTextTexture(const char* p_text, Font p_font)
{
	//SDL_Surface* surface = TTF_RenderText_Blended(p_font.getTTFFont(), p_text, p_font.getColor());
	SDL_Surface* surface = TTF_RenderText_Solid(p_font.getTTFFont(), p_text, p_font.getColor());
	if (surface == nullptr)
	{
		std::cout << "Error creating SDL_Surface: " << SDL_GetError() << std::endl;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr)
	{
		std::cout << "Error creating texture from surface: " << SDL_GetError() << std::endl;
	}

	SDL_FreeSurface(surface);

	Texture tex;
	tex.sdlTexture = texture;
	tex.dimensions = Vector2int(surface->w, surface->h);
	
	return tex;
}

SDL_Texture* Birb2D::RenderWindow::renderTextEntity(Entity& textEntity)
{
	SDL_Surface* surface = TTF_RenderText_Blended(textEntity.getFont().getTTFFont(), textEntity.getText().c_str(), textEntity.getFont().getColor());

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

int Birb2D::RenderWindow::getRefreshRate()
{
	//int displayIndex = SDL_GetWindowDisplayIndex( window );

	//SDL_DisplayMode mode;
	//SDL_GetDisplayMode(displayIndex, 0, &mode);

	//return mode.refresh_rate;
	return refresh_rate;
}

Vector2int Birb2D::RenderWindow::getCursorPosition()
{
	Vector2int pos;
	SDL_GetMouseState(&pos.x, &pos.y);
	return pos;
}

bool Birb2D::RenderWindow::cursorInRect(Rect rect)
{
	Vector2int cursorPos = getCursorPosition();

	// Check for horizontal location
	if (cursorPos.x > rect.x && cursorPos.x < rect.x + rect.w)
	{
		// Check for vertical location
		if (cursorPos.y > rect.y && cursorPos.y < rect.y + rect.h)
		{
			return true;
		}
	}
	return false;
}

void Birb2D::RenderWindow::InitSDL()
{
	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL INIT FAILED: " << SDL_GetError() << "\n";
		exit(2);
	}
	
	// Init SDL_image
	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << "\n";
		exit(2);
	}

	// Init SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cout << "TTF_Init has failed. Error: " << TTF_GetError() << "\n";
		exit(2);
	}
}

void Birb2D::RenderWindow::QuitSDL()
{
	TTF_Quit();
	SDL_Quit();
}

void Birb2D::RenderWindow::cleanUp()
{
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_DestroyWindow(window);
}

void Birb2D::RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void Birb2D::RenderWindow::render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getPos().x;
	dst.y = p_entity.getPos().y;
	dst.w = p_entity.getCurrentFrame().w * p_entity.getLocalScale();
	dst.h = p_entity.getCurrentFrame().h * p_entity.getLocalScale();

	if (dst.w == 0 || dst.h == 0)
	{
		std::cout << "ERROR! Texture with size of 0 in entity " << p_entity.getName() << std::endl;
		return;
	}

	Vector2f centerPoint(p_entity.getCurrentFrame().w / 2, p_entity.getCurrentFrame().h / 2);
	SDL_Point center = { (int)centerPoint.x, (int)centerPoint.y };

	if (SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, p_entity.getAngle(), &center, SDL_FLIP_NONE) < 0)
	{
		std::cout << "Error during rendering: " << SDL_GetError() << ". Entity: " << p_entity.getName() << std::endl;
	}
	//SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void Birb2D::RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void Birb2D::RenderWindow::timestepStart()
{
	startTick = SDL_GetTicks();

	float newTime = utils::hireTimeInSeconds();
	float frameTime = newTime - currentTime;

	if (frameTime > 0.25f)
		frameTime = 0.25f;

	currentTime = newTime;
	accumulator += frameTime;
}

bool Birb2D::RenderWindow::timestepRunning()
{
	return (accumulator >= timeStep);
}

void Birb2D::RenderWindow::timestepStep()
{
	accumulator -= timeStep;
}

void Birb2D::RenderWindow::timestepEnd()
{
	int frameTicks = SDL_GetTicks() - startTick;

	if (frameTicks < 1000 / refresh_rate)
		SDL_Delay(1000 / refresh_rate - frameTicks);
}

float Birb2D::RenderWindow::getTimestepAlpha()
{
	return accumulator / timeStep;
}
