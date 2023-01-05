#pragma once
#ifndef DISTCC
#include "STD.hpp"
#else
#include <string>
#endif

namespace Birb
{
	struct ApplicationInfo
	{
		ApplicationInfo();
		ApplicationInfo(const std::string& ApplicationName);

		/// Application name
		std::string AppName;

		/// Get a path to the data directory of the game
		std::string locate_data_path() const;
	};
}
