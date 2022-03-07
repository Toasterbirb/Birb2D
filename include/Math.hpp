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

		Vector2f(const float& p_x, const float& p_y)
		:x(p_x), y(p_y)
		{}

		std::string toString();

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

		Vector2int(const int& p_x, const int& p_y)
		:x(p_x), y(p_y)
		{}

		Vector2int(const float& p_x, const float& p_y)
		{
			x = std::round(p_x);
			y = std::round(p_y);
		}

		std::string toString();

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

		Vector3f(const float& p_x, const float& p_y, const float& p_z)
		:x(p_x), y(p_y), z(p_z)
		{}

		std::string toString();

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

		Vector3int(const int& p_x, const int& p_y, const int& p_z)
		:x(p_x), y(p_y), z(p_z)
		{}

		Vector3int(const float& p_x, const float& p_y, const float& p_z)
		{
			x = std::round(p_x);
			y = std::round(p_y);
			z = std::round(p_z);
		}

		std::string toString();

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


	/// Misc math functions
	namespace Math
	{
		float VectorDistance(const Vector2f& a, const Vector2f& b); ///< Calculate the distance between two 2D floating point vectors
		float VectorDistance(const Vector2int& a, const Vector2int& b); ///< Calculate the distance between two 2D integer vectors
		float VectorDistance(const Vector3f& a, const Vector3f& b); ///< Calculate the distance between two 3D floating point vectors
		float VectorDistance(const Vector3int& a, const Vector3int& b); ///< Calculate the distance between two 3D integer vectors

		float 		Clamp(const float& value, const float& min, const float& max); ///< Clamp a float between the given values
		double 		Clamp(const double& value, const double& min, const double& max); ///< Clamp a double between the given values
		int 			Clamp(const int& value, const int& min, const int& max); ///< Clamp an integer between the given values

		int 			Lerp(const int& a, const int& b, const float& t); ///< Interpolate a value between two values given time t
		float 		Lerp(const float& a, const float& b, const float& t); ///< Interpolate a value between two values given time t
		Vector2f 	Lerp(const Vector2f& a, const Vector2f& b, const float& t); ///< Interpolate a point between two 2D floating point vectors given time t
		Vector2int 	Lerp(const Vector2int& a, const Vector2int& b, const float& t); ///< Interpolate a point between two 2D integer vectors given time t
		Vector3f 	Lerp(const Vector3f& a, const Vector3f& b, const float& t); ///< Interpolate a point between two 3D floating point vectors given time t
		Vector3int 	Lerp(const Vector3int& a, const Vector3int& b, const float& t); ///< Interpolate a point between two 3D integer vectors given time t

		float 	CenterPoint(const float& a, const float& b); ///< Calculate the "center" value between two 1D floats
		Vector2f CenterPoint(const Vector2f& a, const Vector2f& b); ///< Calculate the center point between two 2D floating point vectors
		Vector2f CenterPoint(const Vector2int& a, const Vector2int& b); ///< Calculate the center point between two 2D integer vectors
		Vector3f CenterPoint(const Vector3f& a, const Vector3f& b); ///< Calculate the center point between two 3D floating point vectors
		Vector3f CenterPoint(const Vector3int& a, const Vector3int& b); ///< Calculate the center point between two 3D integer vectors

		Vector2int FindClosestPoint(const Vector2int& point, Vector2int points[], const int& pointCount);
		Vector2int FindClosestPoint(const Vector2int& point, const std::vector<Vector2int>& points);
		Vector2int FindClosestPoint(const Vector2int& point, const std::vector<Vector2int>& points, const std::vector<Vector2int>& ignoredPoints);

		double 		Round(const double& value, const int& decimal_points); ///< Rounds the given floating point value with specified accuracy

		bool IsDigit(const float& value); 	///< Check if the float has any decimal points
		bool IsDigit(const double& value); 	///< Check if the double has any decimal points


		template<typename T>
		T FindHighestValue(T* values, const int& valueCount)
		{
			T result = values[0];
			for (int i = 1; i < valueCount; i++)
			{
				if (values[i] > result)
					result = values[i];
			}
			return result;
		}

		template<typename T>
		T FindHighestValue(const std::vector<T>& values)
		{
			T result = values[0];
			for (int i = 1; i < (int)values.size(); i++)
			{
				if (values[i] > result)
					result = values[i];
			}
			return result;
		}

		template<typename T>
		T FindLowestValue(T* values, const int& valueCount)
		{
			T result = values[0];
			for (int i = 1; i < valueCount; i++)
			{
				if (values[i] < result)
					result = values[i];
			}
			return result;
		}

		template<typename T>
		T FindLowestValue(const std::vector<T>& values)
		{
			T result = values[0];
			for (int i = 1; i < (int)values.size(); i++)
			{
				if (values[i] < result)
					result = values[i];
			}
			return result;
		}


		template<typename T>
		double Average(T* values, const int& valueCount)
		{
			double total = 0;
			for (int i = 0; i < valueCount; i++)
				total += values[i];
			return total / valueCount;
		}

		double 	Normalize(const double& value, const double& min, const double& max, const double& normalized_maximum);
	};
}
