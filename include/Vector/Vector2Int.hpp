#pragma once

namespace Birb
{
    struct Vector2Int
    {
        int x, y;

        Vector2Int()
        :x(0), y(0)
        {}

        Vector2Int(const int& _x, const int& _y)
        :x(_x), y(_y)
        {}

        Vector2Int(const int values[2])
        :x(values[0]),y(values[1])
        {}

        std::string ToString() const;
        Vector2 ToFloat() const;

        Vector2Int operator+(const Vector2Int& other) const
        {
			return Vector2Int(x + other.x, y + other.y);
        }

        Vector2Int operator-(const Vector2Int& other) const
        {
			return Vector2Int(x - other.x, y - other.y);
        }

        Vector2Int operator*(const Vector2Int& other) const
        {
			return Vector2Int(x * other.x, y * other.y);
        }

        Vector2Int operator*(const int& other) const
        {
			return Vector2Int(x * other, y * other);
        }

        Vector2Int operator/(const Vector2Int& other) const
        {
			return Vector2(static_cast<int>(x / other.x), static_cast<int>(y / other.y));
        }

        Vector2Int operator/(const int& other) const
        {
			return Vector2Int(static_cast<int>(x / other), static_cast<int>(y / other));
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
}