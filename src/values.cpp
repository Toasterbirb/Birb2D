#include <math.h>
#include "Values.hpp"
#include "Filesystem.hpp"
#include "Logger.hpp"

namespace Birb
{
	ApplicationInfo::ApplicationInfo()
	{
		AppName 	= "_null_";
		LocateResources();
	}

	ApplicationInfo::ApplicationInfo(const std::string& ApplicationName)
		:AppName(ApplicationName)
	{
		LocateResources();
	}

	void ApplicationInfo::LocateResources()
	{
		/* Check if the application is in an AppImage */
		char* AppPath = getenv("APPDIR");
		if (AppPath != nullptr)
		{
			/* Application is in an AppImage */
			if (AppName == "_null_")
			{
				/* Application is in an AppImage, but doesn't have AppName set */
				Debug::Log("AppName not set. Resource path defaulted to /usr/share/birb2d/res", Debug::warning);
				ResLocation = (std::string)AppPath + "usr/share/birb2d/res";
			}
			else
			{
				/* Application is in an AppImage and has a AppName set */
				ResLocation = (std::string)AppPath + "usr/share/" + AppName + "/res";
			}

			return;
		}
		

		/* Check if the application name hasn't been set yet */
		if (AppName == "_null_")
		{
			ResLocation = "./res";
			return;
		}

		/* Resource path priority
		 * 1: ./res
		 * 2: ~/.local/share/<ApplicationName>/res
		 * 3: /usr/local/share/<ApplicationName>/res
		 * 4: /usr/share/<ApplicationName>/res */
		
		if (Birb::Filesystem::Directory::Exists("./res"))
			ResLocation = "./res";
		else if (Birb::Filesystem::Directory::Exists((std::string)getenv("HOME") + "/.local/share/" + AppName + "/res"))
			ResLocation = (std::string)getenv("HOME") + "/.local/share/" + AppName + "/res";
		else if (Birb::Filesystem::Directory::Exists("/usr/local/share/" + AppName + "/res"))
			ResLocation = "/usr/local/share/" + AppName + "/res";
		else if (Birb::Filesystem::Directory::Exists("/usr/share/" + AppName + "/res"))
			ResLocation = "/usr/share/" + AppName + "/res";
		else
			ResLocation = "";
	}

	/* Dims or lightens color */
	namespace Colors
	{
		SDL_Color ChangeColorIntensity(const SDL_Color& color, const int& delta)
		{
			SDL_Color newColor = color;

			if (delta > 0)
			{
				// Increase color intensity

				// Red
				if (newColor.r + delta > 255)
					newColor.r = 255;
				else
					newColor.r += delta;

				// Green
				if (newColor.g + delta > 255)
					newColor.g = 255;
				else
					newColor.g += delta;

				// Blue
				if (newColor.b + delta > 255)
					newColor.b = 255;
				else
					newColor.b += delta;
			}
			else
			{
				// Decrease color intensity

				// Red
				if (newColor.r + delta < 0)
					newColor.r = 0;
				else
					newColor.r += delta;

				// Green
				if (newColor.g + delta < 0)
					newColor.g = 0;
				else
					newColor.g += delta;

				// Blue
				if (newColor.b + delta < 0)
					newColor.b = 0;
				else
					newColor.b += delta;
			}

			return newColor;
		}
	}
}
