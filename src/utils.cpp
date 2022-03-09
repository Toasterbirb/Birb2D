#include "Utils.hpp"
#include "Logger.hpp"

namespace Birb
{
	Rect::Rect()
	:x(0.0f), y(0.0f), w(0.0f), h(0.0f)
	{}

	Rect::Rect(const float& p_x, const float& p_y, const float& p_w, const float& p_h)
	:x(p_x), y(p_y), w(p_w), h(p_h)
	{}

	std::string Rect::toString()
	{
		return utils::CleanDecimals(x) + ", " +
			utils::CleanDecimals(y) + ", " +
			utils::CleanDecimals(w) + ", " +
			utils::CleanDecimals(h);
	}

	Vector2f* Rect::toPolygon()
	{
		Vector2f* points = new Vector2f[4] {
			Vector2f(x, y),
			Vector2f(x + w, y),
			Vector2f(x + w, y + h),
			Vector2f(x, y + h)
		};

		return points;
	}

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
		static bool RandomGenInitialized = false;
		void InitRandomGen()
		{
			srand(time(0));
			RandomGenInitialized = true;
		}

		int randomInt(const int& min, const int& max)
		{
			if (!RandomGenInitialized)
				InitRandomGen();

			float value = rand() % (max + 1 - min) + min;
			return value;
		}

		float randomFloat(const float& min, const float& max)
		{
			if (!RandomGenInitialized)
				InitRandomGen();

			float random = ((float) rand()) / (float) RAND_MAX;
			float range = max - min;
			return (random * range) + min;
		}

		void GetTextureDimensions(SDL_Texture* texture, int& x, int& y)
		{
			SDL_QueryTexture(texture, NULL, NULL, &x, &y);
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

		void ShuffleArray(int* values, const int& size)
		{
			int newIndex;
			int placeHolder;
			for (int i = 0; i < size; i++)
			{
				newIndex = randomInt(0, size - 1);
				if (newIndex != i)
				{
					placeHolder = values[i];
					values[i] = values[newIndex];
					values[newIndex] = placeHolder;
				}
			}
		}

		void ShuffleArray(float* values, const int& size)
		{
			int newIndex;
			float placeHolder;
			for (int i = 0; i < size; i++)
			{
				do
				{
					newIndex = randomInt(0, size - 1);
				} while (newIndex == i);

				placeHolder = values[i];
				values[i] = values[newIndex];
				values[newIndex] = placeHolder;
			}
		}

		void ShuffleArray(double* values, const int& size)
		{
			int newIndex;
			double placeHolder;
			for (int i = 0; i < size; i++)
			{
				do
				{
					newIndex = randomInt(0, size - 1);
				} while (newIndex == i);

				placeHolder = values[i];
				values[i] = values[newIndex];
				values[newIndex] = placeHolder;
			}
		}

		void ShuffleArray(std::string* values, const int& size)
		{
			int newIndex;
			std::string placeHolder;
			for (int i = 0; i < size; i++)
			{
				do
				{
					newIndex = randomInt(0, size - 1);
				} while (newIndex == i);

				placeHolder = values[i];
				values[i] = values[newIndex];
				values[newIndex] = placeHolder;
			}
		}

		Line* PolygonToLines(const Vector2f polygon[], const int& polygonSize)
		{
			Line* lines = new Line[polygonSize];
			
			for (int i = 0; i < polygonSize - 1; i++)
			{
				lines[i] = Line(polygon[i], polygon[i + 1]);
			}

			/* The last line connects the last point and the first point */
			lines[polygonSize - 1] = Line(polygon[polygonSize - 1], polygon[0]);

			return lines;
		}
	}
}
