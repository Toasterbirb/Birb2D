#pragma once

#include <SDL2/SDL_ttf.h>
#include <string>

namespace Birb
{
	class Font
	{
	public:
		Font();
		Font(const std::string& filePath, const int& fontSize = 12);
		~Font();
		int size;
		std::string filePath;

		void LoadFont(const std::string& filePath, const int& fontSize = 12);
		bool isLoaded() const;
		TTF_Font* ttf() const;
	
	private:
		bool fontLoaded;
		TTF_Font* ttfFont;
	};
}
