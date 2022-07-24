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

#ifdef SYSTEM_SDL
	std::cout << "- SYSTEM_SDL\tCompiled with pre-compiled system SDL-libs" << std::endl;
#else

#ifdef STATIC_SDL
	std::cout << "- STATIC_SDL\tSDL was compiled with static libraries" << std::endl;
#else
	std::cout << "- SHARED_SDL\tSDL was compiled with shared libraries" << std::endl;
#endif /* STATIC_SDL */

#endif /* SYSTEM_SDL */

#ifdef NO_SOUND
	std::cout << "- NO_SOUND\tDisables sound completely (gets rid of SDL2_mixer dependency)" << std::endl;
#endif

	return 0;
}
