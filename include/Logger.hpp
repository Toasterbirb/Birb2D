#pragma once

#include "STD.hpp"

namespace Birb
{
	namespace Debug
	{
		enum Type
		{
			log, warning, error, fixme
		};
#ifndef __WINDOWS__
		void Reset(); ///< Delete the logfile if one exists already. Good to run on application startup
		static std::string logfile = static_cast<std::string>(getenv("HOME")) + "/.cache/birb2d_log.txt";
#endif
		void Log(const std::string& text, Type type = Type::log); ///< Log to the console and also write to a logfile
		static std::vector<std::string> lines;

		/* Labels that show in between [ ] characters after the timestamp */
		static const std::string LogLabel 		= "L";
		static const std::string WarningLabel 	= "W";
		static const std::string ErrorLabel 	= "E";
		static const std::string FixmeLabel 	= "F";
		std::string ColorLog(const std::string& color_code, const std::string& label, const std::string& text);
	}
}
