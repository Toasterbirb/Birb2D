#include "STD.hpp"
#include "Values.hpp"
#include "Filesystem.hpp"
#include "Logger.hpp"

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
