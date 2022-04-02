#include "Font.hpp"
#include "Logger.hpp"

namespace Birb
{
	Font::Font()
	{
		size = 12;
		filePath = "";
		fontLoaded = false;
	}

	Font::Font(const std::string& filePath, const int& fontSize)
	{
		LoadFont(filePath, fontSize);
	}

	Font::~Font()
	{
		free(ttfFont);
	}

	void Font::LoadFont(const std::string& filePath, const int& fontSize)
	{
		this->filePath 	= filePath;
		this->size 		= fontSize;
		
		/* Attempt to load the font */
		ttfFont = TTF_OpenFont(filePath.c_str(), fontSize);
		if (ttfFont != nullptr)
		{
			fontLoaded = true;
		}
		else
		{
			Debug::Log("Something went wrong when loading font '" + filePath + "' TTF_Error: " + (std::string)TTF_GetError(), Debug::error);
			fontLoaded = false;
		}
	}

	bool Font::isLoaded() const
	{
		return fontLoaded;
	}

	TTF_Font* Font::ttf() const
	{
		return ttfFont;
	}

	int Font::GetSize() const
	{
		return size;
	}

	void Font::SetSize(const int& size)
	{
		this->size = size;

		/* Reload the font with a different size */
		free(ttfFont);
		LoadFont(this->filePath, size);
	}
}
