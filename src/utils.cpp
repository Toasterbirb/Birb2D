#include "Utils.hpp"
#include "Logger.hpp"
#include "STD.hpp"
#include "Vector/Vector2Int.hpp"

namespace Birb
{
	namespace utils
	{
		SDL_Color TexturePixelToColor(Uint8* pixels, const Vector2Int& pixelPosition, int textureWidth)
		{
			// Some weird BGRA format
			Uint8 b = pixels[4 * (pixelPosition.y * textureWidth + pixelPosition.x) + 0]; // Blue
			Uint8 g = pixels[4 * (pixelPosition.y * textureWidth + pixelPosition.x) + 1]; // Green
			Uint8 r = pixels[4 * (pixelPosition.y * textureWidth + pixelPosition.x) + 2]; // Red
			Uint8 a = pixels[4 * (pixelPosition.y * textureWidth + pixelPosition.x) + 3]; // Alpha

			SDL_Color color = { r, g, b, a };

			return color;
		}

		std::vector<Vector2Int> SortPath(const Vector2Int& startPoint, const std::vector<Vector2Int>& points)
		{
			std::vector<Vector2Int> result;
			Vector2Int closestPoint;
			result.push_back(startPoint);

			for (size_t i = 0; i < points.size(); ++i)
			{
				/* Skip the point if its the start point */
				if (startPoint == points[i])
					continue;

				closestPoint = Birb::Math::FindClosestPoint(result[result.size() - 1], points, result);
				result.push_back(closestPoint);
			}

			return result;
		}

		std::string CleanDecimals(double value)
		{
			if (Math::IsDigit(value))
			{
				return std::to_string(static_cast<int>(value));
			}
			else
			{
				std::string result = std::to_string(value);
				size_t size = result.size();
				for (size_t i = size - 1; i > 0; --i)
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

		std::vector<Line> PolygonToLines(const Vector2 polygon[], int polygonSize)
		{
			std::vector<Line> lines;

			/* Abort the mission if there are less than 3 points in the "polygon" */
			if (polygonSize < 3)
				return lines;

			for (int i = 0; i < polygonSize - 1; ++i)
			{
				lines.push_back(Line(polygon[i], polygon[i + 1]));
			}

			/* The last line connects the last point and the first point */
			lines.push_back(Line(polygon[polygonSize - 1], polygon[0]));

			return lines;
		}

		int FlatIndex(const Vector2Int& array_position, const Vector2Int& array_dimensions)
		{
			/* Do some sanity checking */
			if (array_position.x > array_dimensions.x - 1 || array_position.y > array_dimensions.y - 1
					|| array_position.x < 0 || array_position.y < 0)
			{
				return -1;
			}

			if (array_position.y == 0)
				return array_position.x;

			return (array_position.y * array_dimensions.x) + array_position.x;
		}
	}
}
