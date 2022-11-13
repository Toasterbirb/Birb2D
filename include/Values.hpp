#pragma once
#pragma GCC diagnostic ignored "-Wunused-variable"

#include "SDL.hpp"

#include "STD.hpp"
#include "Color.hpp"

namespace Birb
{
	struct ApplicationInfo
	{
		ApplicationInfo();
		ApplicationInfo(const std::string& ApplicationName);

		std::string AppName;
	};

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
	}
}
