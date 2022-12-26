#include "Values.hpp"
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
			context.addFilter("test-case-exclude", "*rendering*,*audio*,*timer*,*input*,*splash*");
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

	/* Check if all SDL things have been shut down properly */
	if (Birb::Global::IsInit::SDL)
		std::cout << "!> SDL wasn't shut down properly <!" << std::endl;

	if (Birb::Global::IsInit::SDL_image)
		std::cout << "!> SDL_image wasn't shut down properly <!" << std::endl;

	if (Birb::Global::IsInit::SDL_mixer)
		std::cout << "!> SDL_mixer wasn't shut down properly <!" << std::endl;

	if (Birb::Global::IsInit::SDL_ttf)
		std::cout << "!> SDL_ttf wasn't shut down properly <!" << std::endl;

	if (context.shouldExit())
		return result;

	return result;
}
