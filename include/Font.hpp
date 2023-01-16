#pragma once

#include "SDL.hpp"

#ifndef DISTCC
#include "STD.hpp"
#else
#include <string>
#endif

#include "ErrorFuse.hpp"

namespace Birb
{
	class Font : public ErrorFuse
	{
	public:
		Font();
		Font(const Font& other);
		Font(const std::string& filePath, const int& fontSize = 12);
		~Font();

		std::string filePath;

		void LoadFont(const std::string& filePath, const int& fontSize = 12);
		bool isLoaded() const;

		TTF_Font* ttf() const;

		int GetSize() const;
		void SetSize(const int& size);

		/* Copy assignment */
		Birb::Font& operator=(const Font& other)
		{
			if (this == &other)
				return *this;

			this->size 			= other.size;
			this->filePath 		= other.filePath;
			this->fontLoaded 	= false;
			this->ttfFont 		= nullptr;

			// TODO: Copy the memory instead of opening the font-file again
			LoadFont(other.filePath, other.size);
			return *this;
		}

	private:
		int size;
		bool fontLoaded;

		TTF_Font* ttfFont;
	};
}
