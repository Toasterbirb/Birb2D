#pragma once

namespace Birb
{
    struct Vector2Int
    {
        int x, y;

        Vector2Int:x(0), y(0) {}
        Vector2Int(const int& _x, const int& _y):x(_x), y(_y) {}
        Vector2Int(const int values[2]):x(values[0]),y(values[1]) {}

        std::string ToString() const;
        Vector2 ToFloat() const;

        #pragma region Add Operator

        Vector2Int operator+(const Vector2Int& other) const
        {
			return Vector2Int(x + other.x, y + other.y);
        }

        #pragma endregion

        #pragma region Subtract Operator

        Vector2Int operator-(const Vector2Int& other) const
        {
			return Vector2Int(x - other.x, y - other.y);
        }

        #pragma endregion

        #pragma region Multiply Operator

        Vector2Int operator*(const Vector2Int& other) const
        {
			return Vector2Int(x * other.x, y * other.y);
        }

        Vector2Int operator*(const int& other) const
        {
			return Vector2Int(x * other, y * other);
        }

        #pragma endregion

        #pragma region Divide Operator

        Vector2Int operator/(const Vector2Int& other) const
        {
			return Vector2(x / other.x, y / other.y);
        }

        Vector2Int operator/(const int& other) const
        {
			return Vector2Int(x / other, y / other);
        }

        #pragma endregion

        #pragma region Is Equal Operator

        bool operator==(const Vector2Int& other) const
		{
			return (x == other.x && y == other.y);
		}

        #pragma endregion

        #pragma region Is Not Equal Operator

		bool operator!=(const Vector2Int& other) const
		{
			return (x != other.x || y != other.y);
		}

       #pragma endregion

       #pragma region Quick Returns

        static Vector2Int One();
        static Vector2Int Zero();
        static Vector2Int Up();
        static Vector2Int Down();
        static Vector2Int Left();
        static Vector2Int Right();

       #pragma endregion
    }
}