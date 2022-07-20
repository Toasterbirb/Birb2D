#pragma once

#include "SDL.hpp"

#include <string>

namespace Birb
{
	class Font
	{
	public:
		Font();
		Font(const std::string& filePath, const int& fontSize = 12);
		~Font();
		std::string filePath;

		void LoadFont(const std::string& filePath, const int& fontSize = 12);
		bool isLoaded() const;

#ifdef LIB_SDL
		TTF_Font* ttf() const;
#endif

		int GetSize() const;
		void SetSize(const int& size);

	private:
		int size;
		bool fontLoaded;

#ifdef LIB_SDL
		TTF_Font* ttfFont;
		void InitSDL_ttf(); ///< Initializes SDL2_ttf (if its not already initialized)
#endif /* LIB_SDL */
	};
}
