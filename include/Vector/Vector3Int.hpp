#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <string>
#include <iostream>
#include <cmath>
#endif

namespace Birb
{
    struct Vector3;
	struct Vector2Int;

    struct Vector3Int
    {
        int x, y, z;

        Vector3Int();
        Vector3Int(const int& x, const int& y, const int& z);
        Vector3Int(const int values[3]);
		Vector3Int(const Vector2Int& vec2);

        Vector3Int(const float& x, const float& y, const float& z);

        std::string ToString() const;
        Vector3 ToFloat() const;

        float magnitude() const; ///< Returns the magnitude of the Vector

        Vector3Int operator+(const Vector3Int& other) const
        {
			return Vector3Int(x + other.x, y + other.y, z + other.z);
        }

        Vector3Int& operator+=(const Vector3Int& other)
        {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
        }

        Vector3Int operator-(const Vector3Int& other) const
        {
			return Vector3Int(x - other.x, y - other.y, z - other.z);
        }

        Vector3Int& operator-=(const Vector3Int& other)
        {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
        }

        Vector3Int operator*(const Vector3Int& other) const
        {
			return Vector3Int(x * other.x, y * other.y, z * other.z);
        }

        Vector3Int& operator*=(const Vector3Int& other)
        {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
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

        Vector3Int& operator/=(const Vector3Int& other)
        {
			x /= static_cast<float>(other.x);
			y /= static_cast<float>(other.y);
			z /= static_cast<float>(other.z);
			return *this;
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

