/*
 * This little program is meant to check what flags were used when
 * compiling Birb2D (or 3D in the future, who knows...)
 */

#include <iostream>

int main(void)
{
	std::cout << "-- Birb2D config tool --\n\nBirb2D has been compiled with the following flags:" << std::endl;

#ifdef DEBUG
	std::cout << "- DEBUG\t\tMore verbosity" << std::endl;
#endif

#ifdef LIB_SDL
	std::cout << "- LIB_SDL\tUse SDL2 as the graphics + sound library" << std::endl;
#endif

#ifdef NO_SOUND
	std::cout << "- NO_SOUND\tDisables sound completely (gets rid of SDL2_mixer dependency)" << std::endl;
#endif

	return 0;
}
