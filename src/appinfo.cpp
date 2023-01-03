#include "AppInfo.hpp"
#include "Filesystem.hpp"

namespace Birb
{
	ApplicationInfo::ApplicationInfo()
	{
		AppName 	= "_null_";
	}

	ApplicationInfo::ApplicationInfo(const std::string& ApplicationName)
		:AppName(ApplicationName)
	{}

	std::string ApplicationInfo::locate_data_path() const
	{
		std::string data_path;

#ifndef __WINDOWS__
		data_path = std::string(getenv("HOME")) + "/.local/share/birb2d/" + AppName;
#else
		data_path = std::string(getenv("APPDATA")) + "/birb2d/" + AppName;
#endif

		/* If the directory doesn't exist yet, create it */
		if (!Birb::Filesystem::Directory::Exists(data_path))
			Birb::Filesystem::Directory::Create(data_path);

		return data_path;
	}
}
