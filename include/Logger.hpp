#pragma once
#include <vector>
#include <iostream>
#include <string.h>

namespace Birb
{
	namespace Debug
	{
		enum Type
		{
			log, warning, error
		};
		void Reset(); ///< Delete the logfile if one exists already. Good to run on application startup
		void Log(const std::string& text, Type type = Type::log); ///< Log to the console and also write to a logfile
		static std::vector<std::string> lines;
	}
}
