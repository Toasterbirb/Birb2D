#pragma once

#include "STD.hpp"

namespace Birb
{
	struct Vector2int;
	struct Vector3int;

	/// Point in 2D space with floating point accuracy
	struct Vector2f
	{
		Vector2f()
		:x(0.0f), y(0.0f)
		{}

		Vector2f(const float& p_x, const float& p_y)
		:x(p_x), y(p_y)
		{}

		Vector2f(const float values[2])
		:x(values[0]), y(values[1])
		{}

		std::string toString() const;
		Vector2int toInt() const;

		/* Operator overloads */
		Vector2f operator+(const Vector2f& other) const
		{
			return Vector2f(x + other.x, y + other.y);
		}

		Vector2f operator-(const Vector2f& other) const
		{
			return Vector2f(x - other.x, y - other.y);
		}

		Vector2f operator*(const Vector2f& other) const
		{
			return Vector2f(x * other.x, y * other.y);
		}

		Vector2f operator/(const Vector2f& other) const
		{
			return Vector2f(x / other.x, y / other.y);
		}

		bool operator==(const Vector2f& other) const
		{
			return (x == other.x && y == other.y);
		}

		bool operator!=(const Vector2f& other) const
		{
			return (x != other.x || y != other.y);
		}

		float x, y;
	};

	/// Point in 2D space with integer accuracy
	struct Vector2int
	{
		Vector2int()
		:x(0), y(0)
		{}

		Vector2int(const int& p_x, const int& p_y)
		:x(p_x), y(p_y)
		{}

		Vector2int(const int values[2])
		:x(values[0]), y(values[1])
		{}

		Vector2int(const float& p_x, const float& p_y)
		{
			x = std::round(p_x);
			y = std::round(p_y);
		}

		std::string toString() const;
		Vector2f toFloat() const;

		/* Operator overloads */
		Vector2int operator+(const Vector2int& other) const
		{
			return Vector2int(x + other.x, y + other.y);
		}

		Vector2int operator-(const Vector2int& other) const
		{
			return Vector2int(x - other.x, y - other.y);
		}

		Vector2int operator*(const Vector2int& other) const
		{
			return Vector2int(x * other.x, y * other.y);
		}

		Vector2int operator/(const Vector2int& other) const
		{
			return Vector2int((int)std::round((float)x / other.x), (int)std::round((float)y / other.y));
		}

		bool operator==(const Vector2int& other) const
		{
			return (x == other.x && y == other.y);
		}

		bool operator!=(const Vector2int& other) const
		{
			return (x != other.x || y != other.y);
		}

		int x, y;
	};

	/// Point in 3D space with floating point accuracy
	struct Vector3f
	{
		Vector3f()
		:x(0.0f), y(0.0f), z(0.0f)
		{}

		Vector3f(const float& p_x, const float& p_y, const float& p_z)
		:x(p_x), y(p_y), z(p_z)
		{}

		Vector3f(const float values[3])
		:x(values[0]), y(values[1]), z(values[2])
		{}

		std::string toString() const;
		Vector3int toInt() const;

		/* Operator overloads */
		Vector3f operator+(const Vector3f& other) const
		{
			return Vector3f(x + other.x, y + other.y, z + other.z);
		}

		Vector3f operator-(const Vector3f& other) const
		{
			return Vector3f(x - other.x, y - other.y, z - other.z);
		}

		Vector3f operator*(const Vector3f& other) const
		{
			return Vector3f(x * other.x, y * other.y, z * other.z);
		}

		Vector3f operator/(const Vector3f& other) const
		{
			return Vector3f(x / other.x, y / other.y, z / other.z);
		}

		bool operator==(const Vector3f& other) const
		{
			return (x == other.x && y == other.y && z == other.z);
		}

		bool operator!=(const Vector3f& other) const
		{
			return (x != other.x || y != other.y || z != other.z);
		}

		float x, y, z;
	};

	/// Point in 3D space with integer accuracy
	struct Vector3int
	{
		Vector3int()
		:x(0), y(0), z(0)
		{}

		Vector3int(const int& p_x, const int& p_y, const int& p_z)
		:x(p_x), y(p_y), z(p_z)
		{}

		Vector3int(const int values[3])
		:x(values[0]), y(values[1]), z(values[2])
		{}

		Vector3int(const float& p_x, const float& p_y, const float& p_z)
		{
			x = std::round(p_x);
			y = std::round(p_y);
			z = std::round(p_z);
		}

		std::string toString() const;
		Vector3f toFloat() const;

		/* Operator overloads */
		Vector3int operator+(const Vector3int& other) const
		{
			return Vector3int(x + other.x, y + other.y, z + other.z);
		}

		Vector3int operator-(const Vector3int& other) const
		{
			return Vector3int(x - other.x, y - other.y, z - other.z);
		}

		Vector3int operator*(const Vector3int& other) const
		{
			return Vector3int(x * other.x, y * other.y, z * other.z);
		}

		Vector3int operator/(const Vector3int& other) const
		{
			return Vector3int((int)std::round((float)x / other.x), (int)std::round((float)y / other.y), (int)std::round((float)z / other.z));
		}

		bool operator==(const Vector3int& other) const
		{
			return (x == other.x && y == other.y && z == other.z);
		}

		bool operator!=(const Vector3int& other) const
		{
			return (x != other.x || y != other.y || z != other.z);
		}

		int x, y, z;
	};

	/* ostream overloads for Vectors */
	inline std::ostream& operator<<(std::ostream& stream, const Vector2int& other)
	{
		stream << other.x << ", " << other.y;
		return stream;
	}

	inline std::ostream& operator<<(std::ostream& stream, const Vector3int& other)
	{
		stream << other.x << ", " << other.y << ", " << other.z;
		return stream;
	}

	inline std::ostream& operator<<(std::ostream& stream, const Vector2f& other)
	{
		stream << other.x << ", " << other.y;
		return stream;
	}

	inline std::ostream& operator<<(std::ostream& stream, const Vector3f& other)
	{
		stream << other.x << ", " << other.y << ", " << other.z;
		return stream;
	}
	/* end of ostream overloads */
}
