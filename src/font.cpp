#include "Font.hpp"
#include "Logger.hpp"
#include "Values.hpp"
#include "Diagnostics.hpp"

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
#ifdef LIB_SDL
		TTF_CloseFont(ttfFont);
#endif /* LIB_SDL */
	}

	void Font::LoadFont(const std::string& filePath, const int& fontSize)
	{
#ifdef LIB_SDL
		InitSDL_ttf();
#endif /* LIB_SDL */

		this->filePath 	= filePath;
		this->size 		= fontSize;
		
		/* Attempt to load the font */
#ifdef LIB_SDL
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
#else
		Debug::Log("Font loading not implemented without SDL_ttf", Debug::fixme);
#endif /* LIB_SDL */
	}

	bool Font::isLoaded() const
	{
		return fontLoaded;
	}

#ifdef LIB_SDL
	TTF_Font* Font::ttf() const
	{
		return ttfFont;
	}
#endif /* LIB_SDL */

	int Font::GetSize() const
	{
		return size;
	}

	void Font::SetSize(const int& size)
	{
		this->size = size;

		/* Reload the font with a different size */
#ifdef LIB_SDL
		TTF_CloseFont(ttfFont);
#endif /* LIB_SDL */

		LoadFont(this->filePath, size);
	}

#ifdef LIB_SDL
	void Font::InitSDL_ttf()
	{
		/* Check if SDL_ttf has already been initialized */
		if (Global::IsInit::SDL_ttf)
			return;

#ifdef DEBUG
		if (Diagnostics::Debugging::InitMessages)
			Debug::Log("Initializing SDL_ttf...");
#endif

		if (TTF_Init() == -1)
		{
			Debug::Log("TTF_Init has failed: " + (std::string)TTF_GetError(), Debug::error);
			exit(2);
		}
		else
		{
			Global::IsInit::SDL_ttf = true;
		}
	}
#endif /* LIB_SDL */
}
