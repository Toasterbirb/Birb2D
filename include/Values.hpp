#pragma once
#include "Font.hpp"
#pragma GCC diagnostic ignored "-Wunused-variable"

#ifndef DISTCC
#include "STD.hpp"
#else
#include <string>
#endif

#include "SDL.hpp"

#include "Color.hpp"
#include "Random.hpp"
#include "Vector/Vector2.hpp"
#include "Vector/Vector2Int.hpp"

namespace Birb
{
	namespace Global
	{
		struct FilePaths
		{
			static inline std::string Resources = "./res/";
		};

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
			static inline Vector2Int WindowDimensions = {0, 0};

			static inline SDL_Window* MainWindow = NULL;
			static inline SDL_Renderer* Renderer = NULL;

			static inline Color BackgroundColor = Color(0, 0, 0);

			static inline Vector2 CameraPosition = {0, 0};
		};

		struct DefaultSettings
		{
			static inline float DefaultVolume = 0.75f;
			static inline Font DefaultFont;
		};

		static inline Random random;
	}
}
