#include "Vector/Vector2.hpp"

namespace Birb
{
    std::string Vector2::ToString() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	}

	Vector2Int Vector2::ToInt() const
	{
		return Vector2Int(std::round(x), std::round(y));
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