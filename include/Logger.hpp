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
		void Log(std::string text, Type type = Type::log);
		static std::vector<std::string> lines;
	}
}
