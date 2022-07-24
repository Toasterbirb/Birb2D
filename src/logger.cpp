#include "Logger.hpp"
#include <ctime>
#include <fstream>
#include <filesystem>

namespace Birb
{
	namespace Debug
	{
		void Reset()
		{
			if (std::filesystem::exists(logfile) && std::filesystem::is_regular_file(logfile))
				std::filesystem::remove(logfile);
		}

		void Log(const std::string& text, Type type)
		{
#ifndef DEBUG
			/* Skip fixme log lines if engine debugging isn't enabled */
			if (type == Debug::fixme)
				return;
#endif

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
					printline = line + "\033[32m[" + LogLabel + "] " + text + "\033[0m";
					line = line + "[" + LogLabel + "] " + text + "\n";
					break;

				case (Type::warning):
					printline = line + "\033[33m[" + WarningLabel +"] " + text + "\033[0m";
					line = line + "[" + WarningLabel + "] " + text + "\n";
					break;

				case (Type::error):
					printline = line + "\033[31m[" + ErrorLabel + "] " + text + "\033[0m";
					line = line + "[" + ErrorLabel + "] " + text + "\n";
					break;

				case (Type::fixme):
					printline = line + "\033[35m[" + FixmeLabel + "] " + text + "\033[0m";
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
				std::cout << printline << std::endl;
			else
			{
				std::cout << printline << " (" << Debug::lines.size() << "x)" << "\t\r" << std::flush;
			}

			// Append the line to a logfile
			std::ofstream outfile;
			outfile.open(logfile, std::ios_base::app);
			outfile << line;
		}
	}
}
