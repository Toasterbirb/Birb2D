#include "Utils.hpp"
#include "Vector/Vector2.hpp"

namespace Birb
{
	Vector2::Vector2()
	:x(0.0f), y(0.0f)
	{}

	Vector2::Vector2(const float& x, const float& y)
	:x(x), y(y)
	{}

	Vector2::Vector2(const float values[2])
	:x(values[0]),y(values[1])
	{}

    std::string Vector2::ToString() const
	{
        return "(" + utils::CleanDecimals(x) + ", " + utils::CleanDecimals(y) + ")";
    }

	Vector2Int Vector2::ToInt() const
	{
		return Vector2Int(std::round(x), std::round(y));
	}

    float Vector2::magnitude() const
    {
        return std::sqrt((x * x) + (y * y));
    }

    Vector2 Vector2::normalized() const
    {
        return *this / magnitude();
    }

    void Vector2::Normalize()
    {
        *this = normalized();
    }

    Vector2 Vector2::One()
    {
        return Vector2(1.0f,1.0f);
    }

    Vector2 Vector2::Zero()
    {
        return Vector2(0.0f,0.0f);
    }

    Vector2 Vector2::Up()
    {
        return Vector2(0.0f,1.0f);
    }

    Vector2 Vector2::Down()
    {
        return Vector2(0.0f,-1.0f);
    }

    Vector2 Vector2::Left()
    {
        return Vector2(-1.0f,0.0f);
    }

    Vector2 Vector2::Right()
    {
        return Vector2(1.0f,0.0f);
    }
}
