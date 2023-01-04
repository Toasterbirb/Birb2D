#pragma once

#include "STD.hpp"
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
		float VectorDistance(const Vector2& a, const Vector2& b); ///< Calculate the distance between two 2D floating point vectors
		float VectorDistance(const Vector2Int& a, const Vector2Int& b); ///< Calculate the distance between two 2D integer vectors
		float VectorDistance(const Vector3& a, const Vector3& b); ///< Calculate the distance between two 3D floating point vectors
		float VectorDistance(const Vector3Int& a, const Vector3Int& b); ///< Calculate the distance between two 3D integer vectors

		template<typename T>
		T Clamp(const T& value, const T& min, const T& max)
		{
			if (value < min)
				return min;
			else if (value > max)
				return max;

			return value;
		}

		template<typename T>
		T Square(const T& value)
		{
			return value * value;
		}

		int 		Lerp(const int& a, const int& b, const float& t); ///< Interpolate a value between two values given time t
		float 		Lerp(const float& a, const float& b, const float& t); ///< Interpolate a value between two values given time t
		double 		Lerp(const double& a, const double& b, const float& t); ///< Interpolate a value between two values given time t
		Vector2 	Lerp(const Vector2& a, const Vector2& b, const float& t); ///< Interpolate a point between two 2D floating point vectors given time t
		Vector2Int 	Lerp(const Vector2Int& a, const Vector2Int& b, const float& t); ///< Interpolate a point between two 2D integer vectors given time t
		Vector3 	Lerp(const Vector3& a, const Vector3& b, const float& t); ///< Interpolate a point between two 3D floating point vectors given time t
		Vector3Int 	Lerp(const Vector3Int& a, const Vector3Int& b, const float& t); ///< Interpolate a point between two 3D integer vectors given time t
		Color 		Lerp(const Color& a, const Color& b, const float& t); ///< Interpolate between two colors given time t

		float 	CenterPoint(const float& a, const float& b); ///< Calculate the "center" value between two 1D floats
		Vector2 CenterPoint(const Vector2& a, const Vector2& b); ///< Calculate the center point between two 2D floating point vectors
		Vector2 CenterPoint(const Vector2Int& a, const Vector2Int& b); ///< Calculate the center point between two 2D integer vectors
		Vector3 CenterPoint(const Vector3& a, const Vector3& b); ///< Calculate the center point between two 3D floating point vectors
		Vector3 CenterPoint(const Vector3Int& a, const Vector3Int& b); ///< Calculate the center point between two 3D integer vectors

		bool PointOnLine(const Line& line, const Vector2& point); ///< Check if the give point is on the line

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


		double Round(const double& value, const int& decimal_points); ///< Rounds the given floating point value with specified accuracy

		bool IsDigit(const float& value); 	///< Check if the float has any decimal points
		bool IsDigit(const double& value); 	///< Check if the double has any decimal points

		/// Find the highest value in an array
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

		/// Find the highest value in a vector
		template<typename T>
		T FindHighestValue(const std::vector<T>& values)
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
		T FindLowestValue(const std::vector<T>& values)
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

		double 	Normalize(const double& value, const double& min, const double& max, const double& normalized_maximum);
	}
}
