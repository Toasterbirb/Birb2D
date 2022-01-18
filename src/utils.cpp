#include "Utils.hpp"

namespace Birb
{
	Rect::Rect()
	:x(0.0f), y(0.0f), w(0.0f), h(0.0f)
	{}

	Rect::Rect(float p_x, float p_y, float p_w, float p_h)
	:x(p_x), y(p_y), w(p_w), h(p_h)
	{}

	Rect Rect::getInt()
	{
		Rect roundedRect;
		roundedRect.x = round(x);
		roundedRect.y = round(y);
		roundedRect.w = round(w);
		roundedRect.h = round(h);

		return roundedRect;
	}

	SDL_Rect Rect::getSDLRect()
	{
		SDL_Rect sdlrect;
		sdlrect.h = h;
		sdlrect.w = w;
		sdlrect.x = x;
		sdlrect.y = y;
		return sdlrect;
	}
}

//Birb2D::Texture::Texture()
//{
//	sdlTexture = NULL;
//	dimensions = Vector2int(-1, -1);
//}
//
//Birb2D::Texture::Texture(SDL_Texture* p_sdlTexture, Vector2int p_dimensions)
//:sdlTexture(p_sdlTexture), dimensions(p_dimensions)
//{}
