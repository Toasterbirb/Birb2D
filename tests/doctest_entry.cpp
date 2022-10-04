#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <iostream>
#include <string.h>

int main(int argc, char** argv)
{
	doctest::Context context;

	/* Simply run the tests, don't do any filtering */
	if (argc == 2)
	{
		if (strcmp(argv[1], "quick") == 0)
		{
			std::cout << "Running quick tests only..." << std::endl;
			context.addFilter("test-case-exclude", "*rendering*,*audio*,*timer*,*input*");
		}
	}

	context.applyCommandLine(argc, argv);

	int result = context.run();

	if (context.shouldExit())
		return result;

	return result;
}
