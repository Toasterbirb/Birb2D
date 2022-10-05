#include "Vector.hpp"

namespace Birb
{
    std::string Vector2::ToString() const
	{
		return "(" + x + ", " + y + ")";
	}

	Vector2Int Vector2::ToInt() const
	{
		return Vector2Int(std::round(x), std::round(y));
	}

    #pragma region Quick Returns

    Vector2 Vector2::One()
    {
        return Vector2(1f,1f);
    }

    Vector2 Vector2::Zero()
    {
        return Vector2(0f,0f);
    }

    Vector2 Vector2::Up()
    {
        return Vector2(0f,1f);
    }

    Vector2 Vector2::Down()
    {
        return Vector2(0f,-1f);
    }

    Vector2 Vector2::Left()
    {
        return Vector2(-1f,0f);
    }

    Vector2 Vector2::Right()
    {
        return Vector2(1f,0f);
    }

    #pragma endregion
}