#pragma once

#include "STD.hpp"

namespace Birb
{
    struct Vector3;

    struct Vector3Int
    {
        int x, y, z;

        Vector3Int()
        :x(0), y(0), z(0)
        {}

        Vector3Int(const int& _x, const int& _y, const int& _z)
        :x(_x), y(_y), z(_z)
        {}

        Vector3Int(const int values[3])
        :x(values[0]),y(values[1]), z(values[2])
        {}

        Vector3Int(const float&_x, const float&_y, const float&_z)
        {
            x = std::round(_x);
            y = std::round(_y);
            z = std::round(_z);
        }

        std::string ToString() const;
        Vector3 ToFloat() const;

        Vector3Int operator+(const Vector3Int& other) const
        {
			return Vector3Int(x + other.x, y + other.y, z + other.z);
        }

        Vector3Int operator-(const Vector3Int& other) const
        {
			return Vector3Int(x - other.x, y - other.y, z - other.z);
        }

        Vector3Int operator*(const Vector3Int& other) const
        {
			return Vector3Int(x * other.x, y * other.y, z * other.z);
        }

        Vector3Int operator*(const int& other) const
        {
			return Vector3Int(x * other, y * other, z * other);
        }

        Vector3Int operator/(const Vector3Int& other) const
        {
            return Vector3Int(
                static_cast<int>(std::round(static_cast<float>(x) / other.x)),
                static_cast<int>(std::round(static_cast<float>(y) / other.y)),
                static_cast<int>(std::round(static_cast<float>(z) / other.z)));
        }

        Vector3Int operator/(const int& other) const
        {
            return Vector3Int(
                static_cast<int>(std::round(static_cast<float>(x) / other)),
                static_cast<int>(std::round(static_cast<float>(y) / other)),
                static_cast<int>(std::round(static_cast<float>(z) / other)));
        }

        bool operator==(const Vector3Int& other) const
		{
			return (x == other.x && y == other.y && z == other.z);
		}

		bool operator!=(const Vector3Int& other) const
		{
			return (x != other.x || y != other.y || z != other.z);
		}

        static Vector3Int One();
        static Vector3Int Zero();
        static Vector3Int Forward();
        static Vector3Int Back();
        static Vector3Int Up();
        static Vector3Int Down();
        static Vector3Int Left();
        static Vector3Int Right();
    };

    inline std::ostream &operator<<(std::ostream &stream, const Vector3Int &other)
    {
        stream << other.x << ", " << other.y << ", " << other.z;
        return stream;
    }
}

