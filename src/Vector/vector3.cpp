#include "Utils.hpp"
#include "Vector/Vector3.hpp"

#ifdef DISTCC
#include <iostream>
#endif

namespace Birb
{
    std::string Vector3::ToString() const
	{
        return "(" + utils::CleanDecimals(x) + ", " + utils::CleanDecimals(y) + ", " + utils::CleanDecimals(z) + ")";
    }

	Vector3Int Vector3::ToInt() const
	{
		return Vector3Int(std::round(x), std::round(y), std::round(z));
	}

    std::ostream &operator<<(std::ostream &stream, const Vector3 &other)
    {
        stream << other.x << ", " << other.y << ", " << other.z;
        return stream;
    }
}
