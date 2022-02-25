#include "Utils.hpp"

namespace Birb
{
	Rect::Rect()
	:x(0.0f), y(0.0f), w(0.0f), h(0.0f)
	{}

	Rect::Rect(const float& p_x, const float& p_y, const float& p_w, const float& p_h)
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

	SDL_Rect Rect::getSDLRect() const
	{
		SDL_Rect sdlrect;
		sdlrect.h = h;
		sdlrect.w = w;
		sdlrect.x = x;
		sdlrect.y = y;
		return sdlrect;
	}

	namespace utils
	{
		std::vector<Vector2int> SortPath(const Vector2int& startPoint, const std::vector<Vector2int>& points)
		{
			std::vector<Vector2int> result;
			Vector2int closestPoint;
			result.push_back(startPoint);

			for (int i = 0; i < (int)points.size(); i++)
			{
				/* Skip the point if its the start point */
				if (startPoint == points[i])
					continue;

				closestPoint = Birb::Math::FindClosestPoint(result[result.size() - 1], points, result);
				result.push_back(closestPoint);
			}

			return result;
		}
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
