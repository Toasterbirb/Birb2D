#include <iostream>
#include <string.h>

int main(int argc, char* argv[])
{
	int curLine = 0;
	std::string output[2];
	for (std::string line; std::getline(std::cin, line);)
	{
		if (curLine == 0)
		{
			output[0] = line;
			curLine++;
			continue;
		}
		else if (curLine == 1)
		{
			output[1] = line;
			curLine++;

			std::cout << "<details>\n" <<
			"\t<summary>" << output[1] << "</summary>\n\n" <<
			output[0] <<
			"\n</details>\n";

			curLine++;
		}
		else
		{
			curLine = 0;
			continue;
		}
	}
	return 0;
}
