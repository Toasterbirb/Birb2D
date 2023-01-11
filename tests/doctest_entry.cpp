#include "SDL.h"
#include "SDL_ttf.h"
#include "Values.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <iostream>
#include <string.h>
#include "Diagnostics.hpp"
#include "AssetManager.hpp"

int main(int argc, char** argv)
{
	doctest::Context context;

	if (argc == 2)
	{
		/* Simply run the tests, don't do any filtering */
		if (strcmp(argv[1], "quick") == 0 || strcmp(argv[1], "--quick") == 0)
		{
			std::cout << "Running quick tests only..." << std::endl;
			context.addFilter("test-case-exclude", "*rendering*,*audio*,*timer*,*input*,*splash*");
		}

		/* Print the help page */
		if (strcmp(argv[1], "help") == 0)
		{
			std::cout << "Note! If you need doctest help page, use arg '--help' instead!" << std::endl;
			std::cout << "\nOptions:\n"\
				<< "\t--filter [doctest filter]\tUse a doctest filter to only run specific tests\n"\
				<< "\t--quick\t\t\t\tOnly run quick non-graphical and non-delayed tests" << std::endl;
			return 0;
		}
	}
	else if (argc == 3)
	{
		/* Use custom filters */
		if (strcmp(argv[1], "--filter") == 0)
		{
			context.addFilter("test-case", argv[2]);
		}
	}

	context.applyCommandLine(argc, argv);

#ifdef BUNDLED_ASSETS
	/* Load assets if they are in the binary */
	Birb::AssetManager::InitializeBundledAssets();
#endif

	/* Enable some debugging things */
	Birb::Diagnostics::Debugging::Overlays::ResourceMonitor = true;

	int result = context.run();

#ifdef BUNDLED_ASSETS
	/* Free the loaded assets */
	Birb::AssetManager::FreeBundledAssets();
#endif

	/* Clear the SDL error buffer since it can be a bit leaky */
	SDL_TLSCleanup();

	/* Check if all SDL things have been shut down properly */
	if (Birb::Global::IsInit::SDL || SDL_WasInit(SDL_INIT_VIDEO))
		std::cout << "!> SDL wasn't shut down properly <!" << std::endl;

	if (Birb::Global::IsInit::SDL_image)
		std::cout << "!> SDL_image wasn't shut down properly <!" << std::endl;

	if (Birb::Global::IsInit::SDL_mixer)
		std::cout << "!> SDL_mixer wasn't shut down properly <!" << std::endl;

	if (Birb::Global::IsInit::SDL_ttf || TTF_WasInit())
		std::cout << "!> SDL_ttf wasn't shut down properly <!" << std::endl;

	if (context.shouldExit())
		return result;

	return result;
}
