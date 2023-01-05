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
    struct Vector2;

    struct Vector2Int
    {
        int x, y;

        Vector2Int();
        Vector2Int(const int& x, const int& y);
        Vector2Int(const int values[2]);
        Vector2Int(const float& x, const float& y);

        std::string ToString() const;
        Vector2 ToFloat() const;

        float magnitude() const; ///< Returns the magnitude of the Vector

        Vector2Int operator+(const Vector2Int& other) const
        {
			return Vector2Int(x + other.x, y + other.y);
        }

        Vector2Int& operator+=(const Vector2Int& other)
        {
			x += other.x;
			y += other.y;
			return *this;
        }

        Vector2Int operator-(const Vector2Int& other) const
        {
			return Vector2Int(x - other.x, y - other.y);
        }

        Vector2Int& operator-=(const Vector2Int& other)
        {
			x -= other.x;
			y -= other.y;
			return *this;
        }

        Vector2Int operator*(const Vector2Int& other) const
        {
			return Vector2Int(x * other.x, y * other.y);
        }

        Vector2Int& operator*=(const Vector2Int& other)
        {
			x *= other.x;
			y *= other.y;
			return *this;
        }

        Vector2Int operator*(const int& other) const
        {
			return Vector2Int(x * other, y * other);
        }

        Vector2Int operator/(const Vector2Int& other) const
        {
            return Vector2Int(
                static_cast<int>(std::round(static_cast<float>(x) / other.x)),
                static_cast<int>(std::round(static_cast<float>(y) / other.y)));
        }

        Vector2Int& operator/=(const Vector2Int& other)
        {
			x /= static_cast<float>(other.x);
			y /= static_cast<float>(other.y);
			return *this;
        }

        Vector2Int operator/(const int& other) const
        {
            return Vector2Int(
                static_cast<int>(std::round(static_cast<float>(x) / other)),
                static_cast<int>(std::round(static_cast<float>(y) / other)));
        }

        bool operator==(const Vector2Int& other) const
		{
			return (x == other.x && y == other.y);
		}

		bool operator!=(const Vector2Int& other) const
		{
			return (x != other.x || y != other.y);
		}

        static Vector2Int One();
        static Vector2Int Zero();
        static Vector2Int Up();
        static Vector2Int Down();
        static Vector2Int Left();
        static Vector2Int Right();
    };

    inline std::ostream &operator<<(std::ostream &stream, const Vector2Int &other)
    {
        stream << other.x << ", " << other.y;
        return stream;
    }
}

