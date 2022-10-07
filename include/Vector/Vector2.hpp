#pragma once

#include "STD.hpp"

namespace Birb
{
    struct Vector2Int;

    struct Vector2
    {
        float x, y;

        Vector2();
        Vector2(const float& x, const float& y);
        Vector2(const float values[2]);

        std::string ToString() const; ///< Returns the Vector as a string
        Vector2Int ToInt() const;     ///< Returns the Vector2 as an Vector2Int

        float magnitude() const; ///< Returns the magnitude of the Vector
        Vector2 normalized() const; ///< Returns the normalization of the Vector
        void Normalize();    ///< Normalizes the Vector

        Vector2 operator+(const Vector2& other) const
        {
			return Vector2(x + other.x, y + other.y);
        }

        Vector2 operator-(const Vector2& other) const
        {
			return Vector2(x - other.x, y - other.y);
        }

        Vector2 operator*(const Vector2& other) const
        {
			return Vector2(x * other.x, y * other.y);
        }

        Vector2 operator*(const float& other) const
        {
			return Vector2(x * other, y * other);
        }

        Vector2 operator/(const Vector2& other) const
        {
			return Vector2(x / other.x, y / other.y);
        }

        Vector2 operator/(const float& other) const
        {
			return Vector2(x / other, y / other);
        }

        bool operator==(const Vector2& other) const
		{
			return (x == other.x && y == other.y);
		}

		bool operator!=(const Vector2& other) const
		{
			return (x != other.x || y != other.y);
		}

        static Vector2 One();
        static Vector2 Zero();
        static Vector2 Up();
        static Vector2 Down();
        static Vector2 Left();
        static Vector2 Right();
    };

    inline std::ostream &operator<<(std::ostream &stream, const Vector2 &other)
    {
        stream << other.x << ", " << other.y;
        return stream;
    }
}

