#pragma once

#include "STD.hpp"

namespace Birb
{
    struct Vector3Int;

    struct Vector3
    {
        float x, y, z;

        Vector3()
        :x(0.0f), y(0.0f), z(0.0f)
        {}

        Vector3(const float& _x, const float& _y, const float& _z)
        :x(_x), y(_y), z(_z)
        {}

        Vector3(const float values[3])
        :x(values[0]),y(values[1]), z(values[2])
        {}

        std::string ToString() const;
        Vector3Int ToInt() const;

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
}