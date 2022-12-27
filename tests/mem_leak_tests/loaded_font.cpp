#include "Font.hpp"
#include "SDL_ttf.h"
int main(void)
{
	TTF_Init();

	/* The font needs to be in its own scope, because otherwise
	 * its deconstructor doesn't have a chance to run before
	 * TTF_Quit() is called */
	{
		Birb::Font font("fonts/freefont/FreeMono.ttf", 32);
	}

	TTF_Quit();
	return 0;
}
