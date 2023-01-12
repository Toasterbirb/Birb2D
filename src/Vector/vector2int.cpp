#include "Vector/Vector2.hpp"
#include "Vector/Vector2Int.hpp"

#ifdef DISTCC
#include <iostream>
#endif

namespace Birb
{
    std::string Vector2Int::ToString() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	}

	Vector2 Vector2Int::ToFloat() const
	{
		return Vector2(x, y);
	}

    std::ostream &operator<<(std::ostream &stream, const Vector2Int &other)
    {
        stream << other.x << ", " << other.y;
        return stream;
    }
}
