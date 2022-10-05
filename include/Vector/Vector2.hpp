#pragma once

namespace Birb
{
    struct Vector2
    {
        float x, y;

        Vector2:x(0f), y(0f) {}
        Vector2(const float& _x, const float& _y):x(_x), y(_y) {}
        Vector2(const float values[2]):x(values[0]),y(values[1]) {}

        std::string ToString() const;
        Vector2Int ToInt() const;

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
}