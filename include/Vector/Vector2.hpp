#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <string>
#include <iosfwd>
#include <cmath>
#endif

namespace Birb
{
	struct Vector2Int;

    struct Vector2
    {
        float x, y;

        constexpr Vector2()
		:x(0.0f), y(0.0f)
		{}

        constexpr Vector2(float x, float y)
		:x(x), y(y)
		{}

        constexpr Vector2(const float values[2])
		:x(values[0]), y(values[1])
		{}

        std::string ToString() const; ///< Returns the Vector as a string
        Vector2Int ToInt() const;     ///< Returns the Vector2 as an Vector2Int

		/// Returns the magnitude of the Vector
        constexpr float magnitude() const
		{
			return std::sqrt((x * x) + (y * y));
		}

		/// Returns the normalization of the Vector
        constexpr Vector2 normalized() const
		{
			return *this / magnitude();
		}

		/// Normalizes the Vector
        constexpr void Normalize()
		{
			*this = normalized();
		}

        constexpr Vector2 operator+(const Vector2& other) const
        {
			return Vector2(x + other.x, y + other.y);
        }

        constexpr Vector2& operator+=(const Vector2& other)
        {
			x += other.x;
			y += other.y;
			return *this;
        }

        constexpr Vector2 operator-(const Vector2& other) const
        {
			return Vector2(x - other.x, y - other.y);
        }

        constexpr Vector2& operator-=(const Vector2& other)
        {
			x -= other.x;
			y -= other.y;
			return *this;
        }

        constexpr Vector2 operator*(const Vector2& other) const
        {
			return Vector2(x * other.x, y * other.y);
        }

        constexpr Vector2& operator*=(const Vector2& other)
        {
			x *= other.x;
			y *= other.y;
			return *this;
        }

        constexpr Vector2 operator*(float other) const
        {
			return Vector2(x * other, y * other);
        }

        constexpr Vector2 operator/(const Vector2& other) const
        {
			return Vector2(x / other.x, y / other.y);
        }

        constexpr Vector2& operator/=(const Vector2& other)
        {
			x /= other.x;
			y /= other.y;
			return *this;
        }

        constexpr Vector2 operator/(float other) const
        {
			return Vector2(x / other, y / other);
        }

        constexpr bool operator==(const Vector2& other) const
		{
			return (x == other.x && y == other.y);
		}

		constexpr bool operator!=(const Vector2& other) const
		{
			return (x != other.x || y != other.y);
		}

        static constexpr Vector2 One()
		{
			return Vector2(1.0f,1.0f);
		}

        static constexpr Vector2 Zero()
		{
			return Vector2(0.0f,0.0f);
		}

        static constexpr Vector2 Up()
		{
			return Vector2(0.0f,1.0f);
		}

        static constexpr Vector2 Down()
		{
			return Vector2(0.0f,-1.0f);
		}

        static constexpr Vector2 Left()
		{
			return Vector2(-1.0f,0.0f);
		}

        static constexpr Vector2 Right()
		{
			return Vector2(1.0f,0.0f);
		}
    };

    std::ostream &operator<<(std::ostream &stream, const Vector2 &other);
}

