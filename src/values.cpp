#include "STD.hpp"
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
		/* Skip all of this if using windows */
#ifdef __WINDOWS__
		ResLocation = "./res";
#else
		/* Check if the application is in an AppImage */
		char* AppPath = getenv("APPDIR");
		if (AppPath != nullptr)
		{
			/* Application is in an AppImage */
			if (AppName == "_null_")
			{
				/* Application is in an AppImage, but doesn't have AppName set */
				Debug::Log("AppName not set. Resource path defaulted to /usr/share/birb2d/res", Debug::warning);
				ResLocation = static_cast<std::string>(AppPath) + "/usr/share/birb2d/res";
			}
			else
			{
				/* Application is in an AppImage and has a AppName set */
				ResLocation = static_cast<std::string>(AppPath) + "/usr/share/" + AppName + "/res";
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
		else if (Birb::Filesystem::Directory::Exists(static_cast<std::string>(getenv("HOME")) + "/.local/share/" + AppName + "/res"))
			ResLocation = static_cast<std::string>(getenv("HOME")) + "/.local/share/" + AppName + "/res";
		else if (Birb::Filesystem::Directory::Exists("/usr/local/share/" + AppName + "/res"))
			ResLocation = "/usr/local/share/" + AppName + "/res";
		else if (Birb::Filesystem::Directory::Exists("/usr/share/" + AppName + "/res"))
			ResLocation = "/usr/share/" + AppName + "/res";
		else
			ResLocation = "";
#endif
	}
}
