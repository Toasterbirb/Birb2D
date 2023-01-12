#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <string>
#include <iosfwd>
#include <cmath>
#endif

#include "Vector/Vector2Int.hpp"

namespace Birb
{
    struct Vector3;

    struct Vector3Int
    {
        int x, y, z;

        constexpr Vector3Int()
		:x(0), y(0), z(0)
		{}

        constexpr Vector3Int(const int& x, const int& y, const int& z)
		:x(x), y(y), z(z)
		{}

        constexpr Vector3Int(const int values[3])
		:x(values[0]),y(values[1]), z(values[2])
		{}

		constexpr Vector3Int(const Vector2Int& vec2)
		:x(vec2.x), y(vec2.y), z(0)
		{}

        constexpr Vector3Int(const float& x, const float& y, const float& z)
		:x(0), y(0), z(0)
		{
			this->x = std::round(x);
			this->y = std::round(y);
			this->z = std::round(z);
		}

        std::string ToString() const;
        Vector3 ToFloat() const;

		/// Returns the magnitude of the Vector
        constexpr float magnitude() const
		{
			return std::sqrt((x * x) + (y * y) + (z * z));
		}

        constexpr Vector3Int operator+(const Vector3Int& other) const
        {
			return Vector3Int(x + other.x, y + other.y, z + other.z);
        }

        constexpr Vector3Int& operator+=(const Vector3Int& other)
        {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
        }

        constexpr Vector3Int operator-(const Vector3Int& other) const
        {
			return Vector3Int(x - other.x, y - other.y, z - other.z);
        }

        constexpr Vector3Int& operator-=(const Vector3Int& other)
        {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
        }

        constexpr Vector3Int operator*(const Vector3Int& other) const
        {
			return Vector3Int(x * other.x, y * other.y, z * other.z);
        }

        constexpr Vector3Int& operator*=(const Vector3Int& other)
        {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
        }

        constexpr Vector3Int operator*(const int& other) const
        {
			return Vector3Int(x * other, y * other, z * other);
        }

        constexpr Vector3Int operator/(const Vector3Int& other) const
        {
            return Vector3Int(
                static_cast<int>(std::round(static_cast<float>(x) / other.x)),
                static_cast<int>(std::round(static_cast<float>(y) / other.y)),
                static_cast<int>(std::round(static_cast<float>(z) / other.z)));
        }

        constexpr Vector3Int& operator/=(const Vector3Int& other)
        {
			x /= static_cast<float>(other.x);
			y /= static_cast<float>(other.y);
			z /= static_cast<float>(other.z);
			return *this;
        }

        constexpr Vector3Int operator/(const int& other) const
        {
            return Vector3Int(
                static_cast<int>(std::round(static_cast<float>(x) / other)),
                static_cast<int>(std::round(static_cast<float>(y) / other)),
                static_cast<int>(std::round(static_cast<float>(z) / other)));
        }

        constexpr bool operator==(const Vector3Int& other) const
		{
			return (x == other.x && y == other.y && z == other.z);
		}

		constexpr bool operator!=(const Vector3Int& other) const
		{
			return (x != other.x || y != other.y || z != other.z);
		}

        static constexpr Vector3Int One()
		{
			return Vector3Int(1,1,1);
		}

        static constexpr Vector3Int Zero()
		{
			return Vector3Int(0,0,0);
		}

        static constexpr Vector3Int Forward()
		{
			return Vector3Int(0,0,1);
		}

        static constexpr Vector3Int Back()
		{
			return Vector3Int(0,0,-1);
		}

        static constexpr Vector3Int Up()
		{
			return Vector3Int(0,1,0);
		}

        static constexpr Vector3Int Down()
		{
			return Vector3Int(0,-1,0);
		}

        static constexpr Vector3Int Left()
		{
			return Vector3Int(-1,0,0);
		}

        static constexpr Vector3Int Right()
		{
			return Vector3Int(1,0,0);
		}
    };

    std::ostream &operator<<(std::ostream &stream, const Vector3Int &other);
}

