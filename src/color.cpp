#include "Color.hpp"
#include "Math.hpp"
#include "Vector/Vector3.hpp"
#include "Vector/Vector3Int.hpp"
#include <iostream>

namespace Birb
{
	SDL_Color Color::sdl() const
	{
		return SDL_Color( { r, g, b, a } );
	}

	void Color::ChangeIntensity(const int& delta)
	{
		int temp_r = r + delta;
		r = Math::Clamp(temp_r, 0, 255);

		int temp_g = g + delta;
		g = Math::Clamp(temp_g, 0, 255);

		int temp_b = b + delta;
		b = Math::Clamp(temp_b, 0, 255);
	}

	std::ostream& operator<<(std::ostream& stream, const Color& other)
	{
		stream << static_cast<short>(other.r) << ", " << static_cast<short>(other.g) << ", " << static_cast<short>(other.b) << ", " << static_cast<short>(other.a);
		return stream;
	}
}
