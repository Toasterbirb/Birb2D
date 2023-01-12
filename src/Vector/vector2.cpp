#include "Utils.hpp"
#include "Vector/Vector2.hpp"
#include "Vector/Vector2Int.hpp"

#ifdef DISTCC
#include <iostream>
#endif

namespace Birb
{
    std::string Vector2::ToString() const
	{
        return "(" + utils::CleanDecimals(x) + ", " + utils::CleanDecimals(y) + ")";
    }

	Vector2Int Vector2::ToInt() const
	{
		return Vector2Int(std::round(x), std::round(y));
	}

    std::ostream &operator<<(std::ostream &stream, const Vector2 &other)
    {
        stream << other.x << ", " << other.y;
        return stream;
    }
}
