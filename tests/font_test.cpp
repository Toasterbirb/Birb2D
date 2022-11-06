#include "doctest.h"
#include "Font.hpp"

namespace Birb
{
	TEST_CASE("Font loading")
	{
		std::string fontPath = "fonts/freefont/FreeMonoBold.ttf";

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
	}
}
