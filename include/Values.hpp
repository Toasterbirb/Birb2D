#pragma once
#pragma GCC diagnostic ignored "-Wunused-variable"

#ifdef LIB_SDL
#include <SDL2/SDL.h>
#endif

#include <string>
#include "Color.hpp"

namespace Birb
{
	struct ApplicationInfo
	{
		ApplicationInfo();
		ApplicationInfo(const std::string& ApplicationName);

		std::string AppName;
		std::string ResLocation;
		void LocateResources();
	};

	namespace Global
	{
		struct IsInit
		{
			static inline bool SDL = false;
			static inline bool SDL_ttf = false;
			static inline bool SDL_image = false;
			static inline bool SDL_mixer = false;
		};

		struct RenderVars
		{
			static inline int RefreshRate = 240;

#ifdef LIB_SDL
			static inline SDL_Window* MainWindow = NULL;
			static inline SDL_Renderer* Renderer = NULL;
#endif

			static inline Color BackgroundColor = Color(0, 0, 0);
		};
	}
}
