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
		std::string filePath;

		void LoadFont(const std::string& filePath, const int& fontSize = 12);
		bool isLoaded() const;
		TTF_Font* ttf() const;

		int GetSize() const;
		void SetSize(const int& size);
	
	private:
		int size;
		bool fontLoaded;
		TTF_Font* ttfFont;
	};
}
