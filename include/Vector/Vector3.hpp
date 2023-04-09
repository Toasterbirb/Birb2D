#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <string>
#include <iosfwd>
#endif

#include "Vector/Vector2.hpp"

namespace Birb
{
    struct Vector3Int;

    struct Vector3
    {
        float x, y, z;

        constexpr Vector3()
		:x(0.0f), y(0.0f), z(0.0f)
		{}

        constexpr Vector3(float x, float y, float z)
		:x(x), y(y), z(z)
		{}

        constexpr Vector3(const float values[3])
		:x(values[0]),y(values[1]), z(values[2])
		{}

		constexpr Vector3(const Vector2& vec2)
		:x(vec2.x), y(vec2.y), z(0)
		{}

        std::string ToString() const;
        Vector3Int ToInt() const;

		/// Returns the magnitude of the Vector
        constexpr float magnitude() const
		{
			return std::sqrt((x * x) + (y * y) + (z * z));
		}

		/// Normalizes the Vector
        constexpr void Normalize()
		{
			*this = normalized();
		}

		/// Returns the normalization of the Vector
        constexpr Vector3 normalized() const
		{
			return *this / magnitude();
		}


        constexpr Vector3 operator+(const Vector3& other) const
        {
			return Vector3(x + other.x, y + other.y, z + other.z);
        }

        constexpr Vector3& operator+=(const Vector3& other)
        {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
        }

        constexpr Vector3 operator-(const Vector3& other) const
        {
			return Vector3(x - other.x, y - other.y, z - other.z);
        }

        constexpr Vector3& operator-=(const Vector3& other)
        {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
        }

        constexpr Vector3 operator*(const Vector3& other) const
        {
			return Vector3(x * other.x, y * other.y, z * other.z);
        }

        constexpr Vector3& operator*=(const Vector3& other)
        {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
        }

        constexpr Vector3 operator*(const float& other) const
        {
			return Vector3(x * other, y * other, z * other);
        }

        constexpr Vector3 operator/(const Vector3& other) const
        {
			return Vector3(x / other.x, y / other.y, z / other.z);
        }

        constexpr Vector3& operator/=(const Vector3& other)
        {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
        }

        constexpr Vector3 operator/(const float& other) const
        {
			return Vector3(x / other, y / other, z / other);
        }

        constexpr bool operator==(const Vector3& other) const
		{
			return (x == other.x && y == other.y && z == other.z);
		}

		constexpr bool operator!=(const Vector3& other) const
		{
			return (x != other.x || y != other.y || z != other.z);
		}

        static constexpr Vector3 One()
		{
			return Vector3(1.0f,1.0f,1.0f);
		}

        static constexpr Vector3 Zero()
		{
			return Vector3(0.0f,0.0f,0.0f);
		}

        static constexpr Vector3 Forward()
		{
			return Vector3(0.0f,0.0f,1.0f);
		}

        static constexpr Vector3 Back()
		{
			return Vector3(0.0f,0.0f,-1.0f);
		}

        static constexpr Vector3 Up()
		{
			return Vector3(0.0f,1.0f,0.0f);
		}

        static constexpr Vector3 Down()
		{
			return Vector3(0.0f,-1.0f,0.0f);
		}

        static constexpr Vector3 Left()
		{
			return Vector3(-1.0f,0.0f,0.0f);
		}

        static constexpr Vector3 Right()
		{
			return Vector3(1.0f,0.0f,0.0f);
		}
    };

    std::ostream &operator<<(std::ostream &stream, const Vector3 &other);
}

