#include "Vector/Vector3.hpp"
#include "Vector/Vector2Int.hpp"
#include "Vector/Vector3Int.hpp"

#ifdef DISTCC
#include <iostream>
#endif

namespace Birb
{
	Vector3Int::Vector3Int()
	:x(0), y(0), z(0)
	{}

	Vector3Int::Vector3Int(const int& x, const int& y, const int& z)
	:x(x), y(y), z(z)
	{}

	Vector3Int::Vector3Int(const int values[3])
	:x(values[0]),y(values[1]), z(values[2])
	{}

	Vector3Int::Vector3Int(const Vector2Int& vec2)
	:x(vec2.x), y(vec2.y), z(0)
	{}

	Vector3Int::Vector3Int(const float& x, const float& y, const float& z)
	{
		this->x = std::round(x);
		this->y = std::round(y);
		this->z = std::round(z);
	}

    std::string Vector3Int::ToString() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
	}

	Vector3 Vector3Int::ToFloat() const
	{
		return Vector3(x, y, z);
	}

    float Vector3Int::magnitude() const
    {
        return std::sqrt((x * x) + (y * y) + (z * z));
    }

    Vector3Int Vector3Int::One()
    {
        return Vector3Int(1,1,1);
    }

    Vector3Int Vector3Int::Zero()
    {
        return Vector3Int(0,0,0);
    }

    Vector3Int Vector3Int::Forward()
    {
        return Vector3Int(0,0,1);
    }

    Vector3Int Vector3Int::Back()
    {
        return Vector3Int(0,0,-1);
    }

    Vector3Int Vector3Int::Up()
    {
        return Vector3Int(0,1,0);
    }

    Vector3Int Vector3Int::Down()
    {
        return Vector3Int(0,-1,0);
    }

    Vector3Int Vector3Int::Left()
    {
        return Vector3Int(-1,0,0);
    }

    Vector3Int Vector3Int::Right()
    {
        return Vector3Int(1,0,0);
    }

    std::ostream &operator<<(std::ostream &stream, const Vector3Int &other)
    {
        stream << other.x << ", " << other.y << ", " << other.z;
        return stream;
    }
}
