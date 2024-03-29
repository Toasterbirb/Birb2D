#include "Font.hpp"
#include "Logger.hpp"
#include "Values.hpp"
#include "Diagnostics.hpp"
#include "AssetManager.hpp"

namespace Birb
{
	Font::Font()
	{
		size = 12;
		filePath = "";
		fontLoaded = false;
	}

	Font::Font(const Font& other)
	{
		this->size 			= other.size;
		this->filePath 		= other.filePath;
		this->fontLoaded 	= false;
		this->ttfFont 		= nullptr;

		// TODO: Copy the memory instead of opening the font-file again
		LoadFont(other.filePath, size);
	}

	Font::Font(const std::string& filePath, const int& fontSize)
	{
		LoadFont(filePath, fontSize);
	}

	Font::~Font()
	{
		if (isLoaded() && ttfFont != nullptr)
		{
			TTF_CloseFont(ttfFont);
			fontLoaded = false;
		}
	}

	void Font::LoadFont(const std::string& filePath, const int& fontSize)
	{
		std::string resource_path = Global::FilePaths::Resources + filePath;
		this->filePath 	= filePath;
		this->size 		= fontSize;

		/* Attempt to load the font */
#ifdef BUNDLED_ASSETS
		ttfFont = TTF_OpenFontRW(AssetManager::sdl_mem_read(filePath), true, fontSize);
#else
		ttfFont = TTF_OpenFont(resource_path.c_str(), fontSize);
#endif

		if (ttfFont != nullptr)
		{
			fontLoaded = true;
		}
		else
		{
			Debug::Log("Something went wrong when loading font '" + resource_path + "' TTF_Error: " + static_cast<std::string>(TTF_GetError()), Debug::error);
			fontLoaded = false;
			BlowErrorFuse();
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
		TTF_CloseFont(ttfFont);

		LoadFont(this->filePath, size);
	}
}
