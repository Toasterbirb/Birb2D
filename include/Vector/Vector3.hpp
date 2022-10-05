#pragma once

namespace Birb
{
    struct Vector3
    {
        float x, y, z;

        Vector3:x(0f), y(0f), z(0f) {}
        Vector3(const float& _x, const float& _y, const float& _z):x(_x), y(_y), z(_z) {}
        Vector3(const float values[3]):x(values[0]),y(values[1]), z(values[2]) {}

        std::string ToString() const;
        Vector3Int ToInt() const;

        #pragma region Add Operator

        Vector3 operator+(const Vector3& other) const
        {
			return Vector3(x + other.x, y + other.y, z + other.z);
        }

        #pragma endregion

        #pragma region Subtract Operator

        Vector3 operator-(const Vector3& other) const
        {
			return Vector3(x - other.x, y - other.y, z - other.z);
        }

        #pragma endregion

        #pragma region Multiply Operator

        Vector3 operator*(const Vector3& other) const
        {
			return Vector3(x * other.x, y * other.y, z * other.z);
        }

        Vector3 operator*(const float& other) const
        {
			return Vector3(x * other, y * other, z * other);
        }

        #pragma endregion

        #pragma region Divide Operator

        Vector3 operator/(const Vector3& other) const
        {
			return Vector3(x / other.x, y / other.y, z / other.z);
        }

        Vector3 operator/(const float& other) const
        {
			return Vector3(x / other, y / other, z / other);
        }

        #pragma endregion

        #pragma region Is Equal Operator

        bool operator==(const Vector3& other) const
		{
			return (x == other.x && y == other.y && z == other.z);
		}

        #pragma endregion

        #pragma region Is Not Equal Operator

		bool operator!=(const Vector3& other) const
		{
			return (x != other.x || y != other.y || z != other.z);
		}

       #pragma endregion

       #pragma region Quick Returns

        static Vector3 One();
        static Vector3 Zero();
        static Vector3 Forward();
        static Vector3 Back();
        static Vector3 Up();
        static Vector3 Down();
        static Vector3 Left();
        static Vector3 Right();

       #pragma endregion
    }
}