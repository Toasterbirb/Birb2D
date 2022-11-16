#include "AppInfo.hpp"

namespace Birb
{
	ApplicationInfo::ApplicationInfo()
	{
		AppName 	= "_null_";
	}

	ApplicationInfo::ApplicationInfo(const std::string& ApplicationName)
		:AppName(ApplicationName)
	{}
}
