#pragma once
#include <iostream>
#include <string.h>

namespace Debug
{
	enum Type
	{
		log, warning, error
	};
	void Log(std::string text, Type type = Type::log);
}
