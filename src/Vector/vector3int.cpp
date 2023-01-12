#include "Vector/Vector3.hpp"
#include "Vector/Vector3Int.hpp"

#ifdef DISTCC
#include <iostream>
#endif

namespace Birb
{
    std::string Vector3Int::ToString() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
	}

	Vector3 Vector3Int::ToFloat() const
	{
		return Vector3(x, y, z);
	}

    std::ostream &operator<<(std::ostream &stream, const Vector3Int &other)
    {
        stream << other.x << ", " << other.y << ", " << other.z;
        return stream;
    }
}
