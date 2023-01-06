#include "Vector/Vector2.hpp"
#include "Vector/Vector2Int.hpp"

#ifdef DISTCC
#include <iostream>
#endif

namespace Birb
{
	Vector2Int::Vector2Int()
	:x(0), y(0)
	{}

	Vector2Int::Vector2Int(const int& x, const int& y)
	:x(x), y(y)
	{}

	Vector2Int::Vector2Int(const int values[2])
	:x(values[0]),y(values[1])
	{}

	Vector2Int::Vector2Int(const float& x, const float& y)
	{
		this->x = std::round(x);
		this->y = std::round(y);
	}

    std::string Vector2Int::ToString() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	}

	Vector2 Vector2Int::ToFloat() const
	{
		return Vector2(x, y);
	}

    float Vector2Int::magnitude() const
    {
        return std::sqrt((x * x) + (y * y));
    }

    Vector2Int Vector2Int::One()
    {
        return Vector2Int(1,1);
    }

    Vector2Int Vector2Int::Zero()
    {
        return Vector2Int(0,0);
    }

    Vector2Int Vector2Int::Up()
    {
        return Vector2Int(0,1);
    }

    Vector2Int Vector2Int::Down()
    {
        return Vector2Int(0,-1);
    }

    Vector2Int Vector2Int::Left()
    {
        return Vector2Int(-1,0);
    }

    Vector2Int Vector2Int::Right()
    {
        return Vector2Int(1,0);
    }

    std::ostream &operator<<(std::ostream &stream, const Vector2Int &other)
    {
        stream << other.x << ", " << other.y;
        return stream;
    }
}
