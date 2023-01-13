#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <vector>
#endif

#include "Vector/Vector2.hpp"
#include "Vector/Vector2Int.hpp"
#include "Vector/Vector3.hpp"
#include "Vector/Vector3Int.hpp"

namespace Birb
{
	class Circle;
	class Color;
	class Line;


	/// Misc math functions
	namespace Math
	{
		/// Multiply the value with itself (power of two)
		template<typename T>
		constexpr T Square(const T& value)
		{
			return value * value;
		}

		/// Calculate the distance between two 2D floating point vectors
		constexpr float VectorDistance(const Vector2& a, const Vector2& b)
		{
			return std::sqrt(Square(b.x - a.x) + Square(b.y - a.y));
		}

		/// Calculate the distance between two 2D integer vectors
		constexpr float VectorDistance(const Vector2Int& a, const Vector2Int& b)
		{
			return std::sqrt(Square(b.x - a.x) + Square(b.y - a.y));
		}

		/// Calculate the distance between two 3D floating point vectors
		constexpr float VectorDistance(const Vector3& a, const Vector3& b)
		{
			return std::sqrt(Square(b.x - a.x) + Square(b.y - a.y) + Square(b.z - a.z));
		}

		/// Calculate the distance between two 3D integer vectors
		constexpr float VectorDistance(const Vector3Int& a, const Vector3Int& b)
		{
			return std::sqrt(Square(b.x - a.x) + Square(b.y - a.y) + Square(b.z - a.z));
		}

		template<typename T>
		constexpr T Clamp(const T& value, const T& min, const T& max)
		{
			if (value < min)
				return min;
			else if (value > max)
				return max;

			return value;
		}

		template<typename T>
		constexpr T Lerp(const T& a, const T& b, const float& t)
		{
			return (a + (b - a) * Clamp(t, 0.0f, 1.0f));
		}

		template<>
		constexpr int Lerp(const int& a, const int& b, const float& t)
		{
			return std::round(a + (b - a) * Clamp(t, 0.0f, 1.0f));
		}

		Vector2Int 	Lerp(const Vector2Int& a, const Vector2Int& b, const float& t);
		Vector3Int 	Lerp(const Vector3Int& a, const Vector3Int& b, const float& t);
		Color 		Lerp(const Color& a, const Color& b, const float& t);

		float 	CenterPoint(const float& a, const float& b); ///< Calculate the "center" value between two 1D floats
		Vector2 CenterPoint(const Vector2& a, const Vector2& b); ///< Calculate the center point between two 2D floating point vectors
		Vector2 CenterPoint(const Vector2Int& a, const Vector2Int& b); ///< Calculate the center point between two 2D integer vectors
		Vector3 CenterPoint(const Vector3& a, const Vector3& b); ///< Calculate the center point between two 3D floating point vectors
		Vector3 CenterPoint(const Vector3Int& a, const Vector3Int& b); ///< Calculate the center point between two 3D integer vectors

		/// @param circle 	Circle object
		/// @param angle 	Angle in degrees
		/// @return 		A point on the circle rotated by the angle.
		Vector2 FindPointOnCircle(const Circle& circle, const float& angle);

		/// Find the closest point in an array to the given Vector2Int point
		/// @param point 		The current point
		/// @param points 		List of points that we are comparing point to
		/// @param pointCount 	Size of the points array
		/// @return 			Closest point in the array
		Vector2Int FindClosestPoint(const Vector2Int& point, Vector2Int points[], const int& pointCount);
		Vector2Int FindClosestPoint(const Vector2Int& point, const std::vector<Vector2Int>& points);
		Vector2Int FindClosestPoint(const Vector2Int& point, const std::vector<Vector2Int>& points, const std::vector<Vector2Int>& ignoredPoints);


		//double Round(const double& value, const int& decimal_points); ///< Rounds the given floating point value with specified accuracy

		template<typename T>
		constexpr double Round(const T& value, const int& decimal_points)
		{
			/* How this thing works:
			 * 1. Multiply the value with 10 ^ decimal points. This will leave the needed values before the decimal point
			 * 2. Round to integer
			 * 3. Divide the value with 10 ^ decimal points to get the desired rounded decimal value
			 * */
			return std::round(value * std::pow(10, decimal_points)) / std::pow(10, decimal_points);
		}

		/// Check if the given value has any decimal points
		template<typename T>
		constexpr bool IsDigit(const T& value)
		{
			return (static_cast<int>(value) == value);
		}

		/// Find the highest value in an array
		template<typename T>
		constexpr T FindHighestValue(T* values, const int& valueCount)
		{
			T result = values[0];
			for (int i = 1; i < valueCount; i++)
			{
				if (values[i] > result)
					result = values[i];
			}
			return result;
		}

		/// Find the highest value in a vector
		template<typename T>
		constexpr T FindHighestValue(const std::vector<T>& values)
		{
			T result = values[0];
			for (size_t i = 1; i < values.size(); i++)
			{
				if (values[i] > result)
					result = values[i];
			}
			return result;
		}

		/// Find the lowest value in an array
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

		/// Find the lowest value in a list
		template<typename T>
		constexpr T FindLowestValue(const std::vector<T>& values)
		{
			T result = values[0];
			for (size_t i = 1; i < values.size(); i++)
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

		template<typename T>
		constexpr double Average(std::vector<T> values)
		{
			double total = 0;
			for (size_t i = 0; i < values.size(); i++)
				total += values[i];
			return total / values.size();
		}

		double 	Normalize(const double& value, const double& min, const double& max, const double& normalized_maximum);
	}
}
