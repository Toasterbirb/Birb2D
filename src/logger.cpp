#include "../include/Logger.hpp"
#include <ctime>
#include <fstream>

void Debug::Log(std::string text, Type type)
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
			printline = line + "\033[32m[Log] " + text + "\033[0m\n";
			line = line + "[Log] " + text + "\n";
			break;

		case (Type::warning):
			printline = line + "\033[33m[Warning] " + text + "\033[0m\n";
			line = line + "[Warning] " + text + "\n";
			break;

		case (Type::error):
			printline = line + "\033[31m[ERROR] " + text + "\033[0m\n";
			line = line + "[ERROR] " + text + "\n";
			break;

		default:
			break;
	}

	// Print out the debug line
	std::cout << printline;

	// Append the line to a logfile
	std::ofstream outfile;
	outfile.open("log.txt", std::ios_base::app);
	outfile << line;
}
