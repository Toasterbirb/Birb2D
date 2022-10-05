#include "Vector.hpp"

namespace Birb
{
    std::string Vector3::ToString() const
	{
		return "(" + x + ", " + y + ", " + z + ")";
	}

	Vector3Int Vector3::ToInt() const
	{
		return Vector3Int(std::round(x), std::round(y), std::round(z));
	}

    #pragma region Quick Returns

    Vector3 Vector3::One()
    {
        return Vector3(1f,1f,1f);
    }

    Vector3 Vector3::Zero()
    {
        return Vector3(0f,0f,0f);
    }

    Vector3 Vector3::Forward()
    {
        return Vector3(0f,0f,1f);
    }

    Vector3 Vector3::Back()
    {
        return Vector3(0f,0f,-1f);
    }

    Vector3 Vector3::Up()
    {
        return Vector3(0f,1f,0f);
    }

    Vector3 Vector3::Down()
    {
        return Vector3(0f,-1f,0f);
    }

    Vector3 Vector3::Left()
    {
        return Vector3(-1f,0f,0f);
    }

    Vector3 Vector3::Right()
    {
        return Vector3(1f,0f,0f);
    }

    #pragma endregion
}