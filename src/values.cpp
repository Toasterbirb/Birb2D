#include <math.h>
#include "Values.hpp"

namespace Birb
{
	/* Dims or lightens color */
	namespace Colors
	{
		SDL_Color ChangeColorIntensity(const SDL_Color& color, const int& delta)
		{
			SDL_Color newColor = color;

			if (delta > 0)
			{
				// Increase color intensity

				// Red
				if (newColor.r + delta > 255)
					newColor.r = 255;
				else
					newColor.r += delta;

				// Green
				if (newColor.g + delta > 255)
					newColor.g = 255;
				else
					newColor.g += delta;

				// Blue
				if (newColor.b + delta > 255)
					newColor.b = 255;
				else
					newColor.b += delta;
			}
			else
			{
				// Decrease color intensity

				// Red
				if (newColor.r + delta < 0)
					newColor.r = 0;
				else
					newColor.r += delta;

				// Green
				if (newColor.g + delta < 0)
					newColor.g = 0;
				else
					newColor.g += delta;

				// Blue
				if (newColor.b + delta < 0)
					newColor.b = 0;
				else
					newColor.b += delta;
			}

			return newColor;
		}
	}
}
