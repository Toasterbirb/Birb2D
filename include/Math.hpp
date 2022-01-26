#pragma once
#include <iostream>
#include <math.h>
#include <vector>

namespace Birb
{
	/// Point in 2D space with floating point accuracy
	struct Vector2f
	{
		Vector2f()
		:x(0.0f), y(0.0f)
		{}

		Vector2f(float p_x, float p_y)
		:x(p_x), y(p_y)
		{}

		Vector2f getValue()
		{
			return Vector2f(x, y);
		}

		std::string print()
		{
			return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
		}

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

		float x, y;
	};

	/// Point in 2D space with integer accuracy
	struct Vector2int
	{
		Vector2int()
		:x(0), y(0)
		{}

		Vector2int(int p_x, int p_y)
		:x(p_x), y(p_y)
		{}

		Vector2int(float p_x, float p_y)
		{
			x = std::round(p_x);
			y = std::round(p_y);
		}

		Vector2int getValue()
		{
			return Vector2int(x, y);
		}

		std::string print()
		{
			return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
		}

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
			return (x == other.x && y == other.y);
		}

		int x, y;
	};

	/// Point in 3D space with floating point accuracy
	struct Vector3f
	{
		Vector3f()
		:x(0.0f), y(0.0f), z(0.0f)
		{}

		Vector3f(float p_x, float p_y, float p_z)
		:x(p_x), y(p_y), z(p_z)
		{}

		Vector3f getValue()
		{
			return Vector3f(x, y, z);
		}

		std::string print()
		{
			return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
		}

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
			return (x == other.x && y == other.y && z == other.z);
		}

		float x, y, z;
	};

	/// Point in 3D space with integer accuracy
	struct Vector3int
	{
		Vector3int()
		:x(0), y(0), z(0)
		{}

		Vector3int(int p_x, int p_y, int p_z)
		:x(p_x), y(p_y), z(p_z)
		{}

		Vector3int(float p_x, float p_y, float p_z)
		{
			x = std::round(p_x);
			y = std::round(p_y);
			z = std::round(p_z);
		}

		Vector3int getValue()
		{
			return Vector3int(x, y, z);
		}

		std::string print()
		{
			return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
		}

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
			return (x == other.x && y == other.y && z == other.z);
		}

		int x, y, z;
	};

	/// Misc math functions
	struct Math
	{
		static float VectorDistance(Vector2f a, Vector2f b); ///< Calculate the distance between two 2D floating point vectors
		static float VectorDistance(Vector2int a, Vector2int b); ///< Calculate the distance between two 2D integer vectors
		static float VectorDistance(Vector3f a, Vector3f b); ///< Calculate the distance between two 3D floating point vectors
		static float VectorDistance(Vector3int a, Vector3int b); ///< Calculate the distance between two 3D integer vectors

		static int 			Lerp(int a, int b, float t); ///< Interpolate a value between two values given time t
		static float 		Lerp(float a, float b, float t); ///< Interpolate a value between two values given time t
		static Vector2f 	Lerp(Vector2f a, Vector2f b, float t); ///< Interpolate a point between two 2D floating point vectors given time t
		static Vector2int 	Lerp(Vector2int a, Vector2int b, float t); ///< Interpolate a point between two 2D integer vectors given time t
		static Vector3f 	Lerp(Vector3f a, Vector3f b, float t); ///< Interpolate a point between two 3D floating point vectors given time t
		static Vector3int 	Lerp(Vector3int a, Vector3int b, float t); ///< Interpolate a point between two 3D integer vectors given time t

		static float 	CenterPoint(float a, float b); ///< Calculate the "center" value between two 1D floats
		static Vector2f CenterPoint(Vector2f a, Vector2f b); ///< Calculate the center point between two 2D floating point vectors
		static Vector2f CenterPoint(Vector2int a, Vector2int b); ///< Calculate the center point between two 2D integer vectors
		static Vector3f CenterPoint(Vector3f a, Vector3f b); ///< Calculate the center point between two 3D floating point vectors
		static Vector3f CenterPoint(Vector3int a, Vector3int b); ///< Calculate the center point between two 3D integer vectors

		static Vector2int FindClosestPoint(Vector2int point, Vector2int points[], int pointCount);
		static Vector2int FindClosestPoint(Vector2int point, std::vector<Vector2int> points);
		static Vector2int FindClosestPoint(Vector2int point, std::vector<Vector2int> points, std::vector<Vector2int> ignoredPoints);
	};
}
