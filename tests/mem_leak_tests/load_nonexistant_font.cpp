#include "Font.hpp"
#include <iostream>

int main(void)
{
	std::cout << " > Load a font that doesn't exist and quit the program immediately" << std::endl;
	Birb::Font font("some_font_that_doesn't_exist.ttf", 32);

	/* Clear the SDL error buffer since it can be a bit leaky */
	SDL_TLSCleanup();

	return 0;
}
