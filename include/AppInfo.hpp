#pragma once
#include "STD.hpp"

namespace Birb
{
	struct ApplicationInfo
	{
		ApplicationInfo();
		ApplicationInfo(const std::string& ApplicationName);

		/// Application name
		std::string AppName;
	};
}
