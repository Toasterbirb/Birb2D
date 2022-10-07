#pragma once

#include "STD.hpp"

namespace Birb
{
    struct Vector3Int;
	struct Vector2;

    struct Vector3
    {
        float x, y, z;

        Vector3()
        :x(0.0f), y(0.0f), z(0.0f)
        {}

        Vector3(const float& x, const float& y, const float& z)
        :x(x), y(y), z(z)
        {}

        Vector3(const float values[3])
        :x(values[0]),y(values[1]), z(values[2])
        {}

		Vector3(const Vector2& vec2);

        std::string ToString() const;
        Vector3Int ToInt() const;

        float magnitude() const;    ///< Returns the magnitude of the Vector
        Vector3 normalized() const; ///< Returns the normalization of the Vector
        void Normalize();           ///< Normalizes the Vector

        Vector3 operator+(const Vector3& other) const
        {
			return Vector3(x + other.x, y + other.y, z + other.z);
        }

        Vector3 operator-(const Vector3& other) const
        {
			return Vector3(x - other.x, y - other.y, z - other.z);
        }

        Vector3 operator*(const Vector3& other) const
        {
			return Vector3(x * other.x, y * other.y, z * other.z);
        }

        Vector3 operator*(const float& other) const
        {
			return Vector3(x * other, y * other, z * other);
        }

        Vector3 operator/(const Vector3& other) const
        {
			return Vector3(x / other.x, y / other.y, z / other.z);
        }

        Vector3 operator/(const float& other) const
        {
			return Vector3(x / other, y / other, z / other);
        }

        bool operator==(const Vector3& other) const
		{
			return (x == other.x && y == other.y && z == other.z);
		}

		bool operator!=(const Vector3& other) const
		{
			return (x != other.x || y != other.y || z != other.z);
		}

        static Vector3 One();
        static Vector3 Zero();
        static Vector3 Forward();
        static Vector3 Back();
        static Vector3 Up();
        static Vector3 Down();
        static Vector3 Left();
        static Vector3 Right();
    };

    inline std::ostream &operator<<(std::ostream &stream, const Vector3 &other)
    {
        stream << other.x << ", " << other.y << ", " << other.z;
        return stream;
    }
}

