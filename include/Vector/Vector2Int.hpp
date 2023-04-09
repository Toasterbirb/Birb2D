#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <string>
#include <cmath>
#include <iosfwd>
#endif

namespace Birb
{
    struct Vector2;

    struct Vector2Int
    {
        int x, y;

        constexpr Vector2Int()
		:x(0), y(0)
		{}

        constexpr Vector2Int(int x, int y)
		:x(x), y(y)
		{}

        constexpr Vector2Int(const int values[2])
		:x(values[0]), y(values[1])
		{}

        constexpr Vector2Int(float x, float y)
		:x(0), y(0)
		{
			this->x = std::round(x);
			this->y = std::round(y);
		}


        std::string ToString() const;
        Vector2 ToFloat() const;

		/// Returns the magnitude of the Vector
        constexpr float magnitude() const
		{
			return std::sqrt((x * x) + (y * y));
		}

        constexpr Vector2Int operator+(const Vector2Int& other) const
        {
			return Vector2Int(x + other.x, y + other.y);
        }

        constexpr Vector2Int& operator+=(const Vector2Int& other)
        {
			x += other.x;
			y += other.y;
			return *this;
        }

        constexpr Vector2Int operator-(const Vector2Int& other) const
        {
			return Vector2Int(x - other.x, y - other.y);
        }

        constexpr Vector2Int& operator-=(const Vector2Int& other)
        {
			x -= other.x;
			y -= other.y;
			return *this;
        }

        constexpr Vector2Int operator*(const Vector2Int& other) const
        {
			return Vector2Int(x * other.x, y * other.y);
        }

        constexpr Vector2Int& operator*=(const Vector2Int& other)
        {
			x *= other.x;
			y *= other.y;
			return *this;
        }

        constexpr Vector2Int operator*(int other) const
        {
			return Vector2Int(x * other, y * other);
        }

        constexpr Vector2Int operator/(const Vector2Int& other) const
        {
            return Vector2Int(
                static_cast<int>(std::round(static_cast<float>(x) / other.x)),
                static_cast<int>(std::round(static_cast<float>(y) / other.y)));
        }

        constexpr Vector2Int& operator/=(const Vector2Int& other)
        {
			x /= static_cast<float>(other.x);
			y /= static_cast<float>(other.y);
			return *this;
        }

        constexpr Vector2Int operator/(int other) const
        {
            return Vector2Int(
                static_cast<int>(std::round(static_cast<float>(x) / other)),
                static_cast<int>(std::round(static_cast<float>(y) / other)));
        }

        constexpr bool operator==(const Vector2Int& other) const
		{
			return (x == other.x && y == other.y);
		}

		constexpr bool operator!=(const Vector2Int& other) const
		{
			return (x != other.x || y != other.y);
		}

        static constexpr Vector2Int One()
		{
			return Vector2Int(1,1);
		}

        static constexpr Vector2Int Zero()
		{
			return Vector2Int(0,0);
		}
        static constexpr Vector2Int Up()
		{
			return Vector2Int(0,1);
		}

        static constexpr Vector2Int Down()
		{
			return Vector2Int(0,-1);
		}

        static constexpr Vector2Int Left()
		{
			return Vector2Int(-1,0);
		}

        static constexpr Vector2Int Right()
		{
			return Vector2Int(1,0);
		}
    };

    std::ostream &operator<<(std::ostream &stream, const Vector2Int &other);
}

