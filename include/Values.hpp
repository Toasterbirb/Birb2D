#pragma once
#pragma GCC diagnostic ignored "-Wunused-variable"

#include <SDL2/SDL.h>
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
			static inline SDL_Window* MainWindow = NULL;
			static inline SDL_Renderer* Renderer = NULL;
			static inline Color BackgroundColor = Color(0, 0, 0);
		};
	}

	namespace Colors
	{
		static Color White =        { 255, 	255, 	255, 	255 };
		static Color Black =        { 0, 	0, 		0, 		255 };
		static Color Red =          { 255, 	0, 		0, 		255 };
		static Color Green =        { 0, 	255, 	0, 		255 };
		static Color Blue =         { 0, 	0, 		255, 	255 };
		static Color Yellow =       { 255, 	255, 	0, 		255 };
		static Color DarkGray =     { 60, 	60, 	60, 	255 };
		static Color LightGray =    { 180, 	180, 	180, 	255 };

		SDL_Color ChangeColorIntensity(const SDL_Color& color, const int& delta);
	}
}
