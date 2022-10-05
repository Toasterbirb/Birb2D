#pragma once

namespace Birb
{
    struct Vector3Int
    {
        int x, y, z;

        Vector3Int:x(0), y(0), z(0) {}
        Vector3Int(const int& _x, const int& _y, const int& _z):x(_x), y(_y), z(_z) {}
        Vector3Int(const int values[3]):x(values[0]),y(values[1]), z(values[2]) {}

        std::string ToString() const;
        Vector3 ToFloat() const;

        #pragma region Add Operator

        Vector3Int operator+(const Vector3Int& other) const
        {
			return Vector3Int(x + other.x, y + other.y, z + other.z);
        }

        #pragma endregion

        #pragma region Subtract Operator

        Vector3Int operator-(const Vector3Int& other) const
        {
			return Vector3Int(x - other.x, y - other.y, z - other.z);
        }

        #pragma endregion

        #pragma region Multiply Operator

        Vector3Int operator*(const Vector3Int& other) const
        {
			return Vector3Int(x * other.x, y * other.y, z * other.z);
        }

        Vector3Int operator*(const int& other) const
        {
			return Vector3Int(x * other, y * other, z * other);
        }

        #pragma endregion

        #pragma region Divide Operator

        Vector3Int operator/(const Vector3Int& other) const
        {
			return Vector3Int(x / other.x, y / other.y, z / other.z);
        }

        Vector3Int operator/(const int& other) const
        {
			return Vector3Int(x / other, y / other, z / other);
        }

        #pragma endregion

        #pragma region Is Equal Operator

        bool operator==(const Vector3Int& other) const
		{
			return (x == other.x && y == other.y && z == other.z);
		}

        #pragma endregion

        #pragma region Is Not Equal Operator

		bool operator!=(const Vector3Int& other) const
		{
			return (x != other.x || y != other.y || z != other.z);
		}

       #pragma endregion

       #pragma region Quick Returns

        static Vector3Int One();
        static Vector3Int Zero();
        static Vector3Int Forward();
        static Vector3Int Back();
        static Vector3Int Up();
        static Vector3Int Down();
        static Vector3Int Left();
        static Vector3Int Right();

       #pragma endregion
    }
}