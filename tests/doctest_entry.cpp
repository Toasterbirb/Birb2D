#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <iostream>
#include <string.h>
#include "AssetManager.hpp"

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

#ifdef BUNDLED_ASSETS
	/* Load assets if they are in the binary */
	Birb::AssetManager::InitializeBundledAssets();
#endif

	int result = context.run();

#ifdef BUNDLED_ASSETS
	/* Free the loaded assets */
	Birb::AssetManager::FreeBundledAssets();
#endif

	if (context.shouldExit())
		return result;

	return result;
}
