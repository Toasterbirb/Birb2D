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
        namespace Debugging
        {
            static bool Buttons     = false;
        }

		namespace IsInit
		{
			static bool SDL 		= false;
			static bool SDL_ttf 	= false;
			static bool SDL_image 	= false;
		}

		namespace RenderVars
		{
			static int RefreshRate = 240;
			static SDL_Window* MainWindow;
			static SDL_Renderer* Renderer;
			static Color BackgroundColor = 0x000000;
		}
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
