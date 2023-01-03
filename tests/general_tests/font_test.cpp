#include "SDL_ttf.h"
#include "doctest.h"
#include "Font.hpp"
#include <chrono>

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Font loading")
	{
		std::string fontPath = "fonts/freefont/FreeMonoBold.ttf";
		TTF_Init();

		SUBCASE("With not parameters given to constructor")
		{
			Font font;
			CHECK(font.isLoaded() == false);
			font.LoadFont(fontPath, 13);

			CHECK(font.GetSize() == 13);
			CHECK(font.isLoaded());
		}

		SUBCASE("With constructor parameters")
		{
			Font font(fontPath, 14);
			CHECK(font.GetSize() == 14);
			CHECK(font.isLoaded());
		}

		SUBCASE("Change the font size")
		{
			Font font(fontPath, 14);
			CHECK(font.GetSize() == 14);
			CHECK(font.isLoaded());

			font.SetSize(15);
			CHECK(font.GetSize() == 15);
			CHECK(font.isLoaded());
		}

		SUBCASE("Create a copy of a Font object")
		{
			Font font(fontPath, 14);
			Font second_font = font;

			CHECK(second_font.GetSize() == font.GetSize());
			CHECK(second_font.isLoaded());
			CHECK(second_font.filePath == font.filePath);

			/* The ttf font pointer shouldn't be the same in both fonts
			 * because that would result in a double free */
			CHECK_FALSE(font.ttf() == second_font.ttf());
		}

		TTF_Quit();
	}
}
