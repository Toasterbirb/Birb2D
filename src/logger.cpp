#include "Logger.hpp"

#ifdef DISTCC
#include <filesystem>
#include <iostream>
#include <fstream>
#endif

namespace Birb
{
	namespace Debug
	{
#ifndef __WINDOWS__
		void Reset()
		{
			if (std::filesystem::exists(logfile) && std::filesystem::is_regular_file(logfile))
				std::filesystem::remove(logfile);
		}
#endif

		std::string ColorLog(const std::string& color_code, const std::string& label, const std::string& text)
		{
#ifndef __WINDOWS__
			return "\033[" + color_code + "m[" + label + "] " + text + "\033[0m";
#else
			/* Skip colors on windows since the windows CLI isn't
			 * capable of showing them and thus the color codes
			 * only clutter the program output */
			return "[" + label + "] " + text;
#endif
		}

		void Log(const std::string& text, Type type)
		{
			std::time_t t = std::time(0);
			std::tm* now = std::localtime(&t);
			std::string hours, minutes, seconds;

			std::string line;
			std::string printline;

			// Hours
			if (now->tm_hour < 10)
				hours = "0" + std::to_string(now->tm_hour);
			else
				hours = std::to_string(now->tm_hour);

			// Minutes
			if (now->tm_min < 10)
				minutes = "0" + std::to_string(now->tm_min);
			else
				minutes = std::to_string(now->tm_min);

			// Seconds
			if (now->tm_sec < 10)
				seconds = "0" + std::to_string(now->tm_sec);
			else
				seconds = std::to_string(now->tm_sec);

			line = "[" + hours + ":" + minutes + ":" + seconds + "] ";


			switch (type)
			{
				case (Type::log):
					printline = line + ColorLog("32", LogLabel, text);
					line = line + "[" + LogLabel + "] " + text + "\n";
					break;

				case (Type::warning):
					printline = line + ColorLog("33", WarningLabel, text);
					line = line + "[" + WarningLabel + "] " + text + "\n";
					break;

				case (Type::error):
					printline = line + ColorLog("31", ErrorLabel, text);
					line = line + "[" + ErrorLabel + "] " + text + "\n";
					break;

				case (Type::fixme):
					printline = line + ColorLog("35", FixmeLabel, text);
					line = line + "[" + FixmeLabel + "] " + text + "\n";

				default:
					break;
			}

			// Add the text to list of debug lines
			bool repeatingLine = false;

			if (Debug::lines.size() > 0)
			{
				if (Debug::lines[Debug::lines.size() - 1] == text)
				{
					repeatingLine = true;
					Debug::lines.push_back(text);
				}
				else if (Debug::lines.size() > 1)
				{
					Debug::lines.clear();
					std::cout << "\n";
				}
				else
				{
					Debug::lines.clear();
				}
			}
			else
			{
				Debug::lines.push_back(text);
			}

			// Print out the debug line
			if (!repeatingLine)
				std::cout << printline << '\n';
			else
			{
				std::cout << printline << " (" << Debug::lines.size() << "x)" << "\t\r" << std::flush;
			}

			// Append the line to a logfile
#ifndef __WINDOWS__
			std::ofstream outfile;
			outfile.open(logfile, std::ios_base::app);
			outfile << line;
#endif
		}
	}
}
