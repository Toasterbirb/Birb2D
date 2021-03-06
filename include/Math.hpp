#pragma once

#include "STD.hpp"
#include "Vector.hpp"
#include "Color.hpp"
#include "Circle.hpp"
#include "Line.hpp"

namespace Birb
{


	/// Misc math functions
	namespace Math
	{
		float VectorDistance(const Vector2f& a, const Vector2f& b); ///< Calculate the distance between two 2D floating point vectors
		float VectorDistance(const Vector2int& a, const Vector2int& b); ///< Calculate the distance between two 2D integer vectors
		float VectorDistance(const Vector3f& a, const Vector3f& b); ///< Calculate the distance between two 3D floating point vectors
		float VectorDistance(const Vector3int& a, const Vector3int& b); ///< Calculate the distance between two 3D integer vectors

		template<typename T>
		T Clamp(const T& value, const T& min, const T& max)
		{
			if (value < min)
				return min;
			else if (value > max)
				return max;

			return value;
		}

		int 		Lerp(const int& a, const int& b, const float& t); ///< Interpolate a value between two values given time t
		float 		Lerp(const float& a, const float& b, const float& t); ///< Interpolate a value between two values given time t
		double 		Lerp(const double& a, const double& b, const float& t); ///< Interpolate a value between two values given time t
		Vector2f 	Lerp(const Vector2f& a, const Vector2f& b, const float& t); ///< Interpolate a point between two 2D floating point vectors given time t
		Vector2int 	Lerp(const Vector2int& a, const Vector2int& b, const float& t); ///< Interpolate a point between two 2D integer vectors given time t
		Vector3f 	Lerp(const Vector3f& a, const Vector3f& b, const float& t); ///< Interpolate a point between two 3D floating point vectors given time t
		Vector3int 	Lerp(const Vector3int& a, const Vector3int& b, const float& t); ///< Interpolate a point between two 3D integer vectors given time t
		Color 		Lerp(const Color& a, const Color& b, const float& t); ///< Interpolate between two colors given time t

		float 	CenterPoint(const float& a, const float& b); ///< Calculate the "center" value between two 1D floats
		Vector2f CenterPoint(const Vector2f& a, const Vector2f& b); ///< Calculate the center point between two 2D floating point vectors
		Vector2f CenterPoint(const Vector2int& a, const Vector2int& b); ///< Calculate the center point between two 2D integer vectors
		Vector3f CenterPoint(const Vector3f& a, const Vector3f& b); ///< Calculate the center point between two 3D floating point vectors
		Vector3f CenterPoint(const Vector3int& a, const Vector3int& b); ///< Calculate the center point between two 3D integer vectors

		bool PointOnLine(const Line& line, const Vector2f& point); ///< Check if the give point is on the line

		/// @param circle 	Circle object
		/// @param angle 	Angle in degrees
		/// @return 		A point on the circle rotated by the angle.
		Vector2f FindPointOnCircle(const Circle& circle, const float& angle);

		/// Find the closest point in an array to the given Vector2int point
		/// @param point 		The current point
		/// @param points 		List of points that we are comparing point to
		/// @param pointCount 	Size of the points array
		/// @return 			Closest point in the array
		Vector2int FindClosestPoint(const Vector2int& point, Vector2int points[], const int& pointCount);
		Vector2int FindClosestPoint(const Vector2int& point, const std::vector<Vector2int>& points);
		Vector2int FindClosestPoint(const Vector2int& point, const std::vector<Vector2int>& points, const std::vector<Vector2int>& ignoredPoints);


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
			for (int i = 1; i < (int)values.size(); i++)
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
