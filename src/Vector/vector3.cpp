#include "Vector.hpp"

namespace Birb
{
    std::string Vector3::ToString() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
	}

	Vector3Int Vector3::ToInt() const
	{
		return Vector3Int(std::round(x), std::round(y), std::round(z));
	}

    Vector3 Vector3::One()
    {
        return Vector3(1.0f,1.0f,1.0f);
    }

    Vector3 Vector3::Zero()
    {
        return Vector3(0.0f,0.0f,0.0f);
    }

    Vector3 Vector3::Forward()
    {
        return Vector3(0.0f,0.0f,1.0f);
    }

    Vector3 Vector3::Back()
    {
        return Vector3(0.0f,0.0f,-1.0f);
    }

    Vector3 Vector3::Up()
    {
        return Vector3(0.0f,1.0f,0.0f);
    }

    Vector3 Vector3::Down()
    {
        return Vector3(0.0f,-1.0f,0.0f);
    }

    Vector3 Vector3::Left()
    {
        return Vector3(-1.0f,0.0f,0.0f);
    }

    Vector3 Vector3::Right()
    {
        return Vector3(1.0f,0.0f,0.0f);
    }
}