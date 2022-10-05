#include "Vector.hpp"

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
}