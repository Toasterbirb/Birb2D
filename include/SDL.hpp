#pragma once
#ifdef LIB_SDL

#ifdef SYSTEM_SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#endif /* SYSTEM_SDL */

#endif /* LIB_SDL */
