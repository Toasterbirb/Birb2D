#include "Utils.hpp"
#include "Logger.hpp"

namespace Birb
{
	namespace utils
	{
#ifdef LIB_SDL
		Vector2int GetTextureDimensions(SDL_Texture* texture)
		{
			Vector2int result;
			SDL_QueryTexture(texture, NULL, NULL, &result.x, &result.y);
			return result;
		}

		SDL_Color TexturePixelToColor(Uint8* pixels, const Vector2int& pixelPosition, const int& textureWidth)
		{
			// Some weird BGRA format
			Uint8 b = pixels[4 * (pixelPosition.y * textureWidth + pixelPosition.x) + 0]; // Blue
			Uint8 g = pixels[4 * (pixelPosition.y * textureWidth + pixelPosition.x) + 1]; // Green
			Uint8 r = pixels[4 * (pixelPosition.y * textureWidth + pixelPosition.x) + 2]; // Red
			Uint8 a = pixels[4 * (pixelPosition.y * textureWidth + pixelPosition.x) + 3]; // Alpha
			
			SDL_Color color = { r, g, b, a };
			
			return color;
		}
#endif /* LIB_SDL */

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

		std::string CleanDecimals(const double& value)
		{
			if (Math::IsDigit(value))
			{
				return std::to_string((int)value);
			}
			else
			{
				std::string result = std::to_string(value);
				int size = (int)result.size();
				for (int i = size - 1; i > 0; i--)
				{
					if (result[i] != '0' && i < size - 1)
					{
						result.erase(i + 1, size);
						break;
					}
				}

				return result;
			}
		}

		std::vector<Line> PolygonToLines(const Vector2f polygon[], const int& polygonSize)
		{
			std::vector<Line> lines;
			
			for (int i = 0; i < polygonSize - 1; i++)
			{
				lines.push_back(Line(polygon[i], polygon[i + 1]));
			}

			/* The last line connects the last point and the first point */
			lines[polygonSize - 1] = Line(polygon[polygonSize - 1], polygon[0]);

			return lines;
		}
	}
}
