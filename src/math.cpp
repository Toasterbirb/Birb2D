#include "Math.hpp"
#include "Logger.hpp"

namespace Birb
{
	float Math::VectorDistance(const Vector2f& a, const Vector2f& b)
	{
		return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
	}

	float Math::VectorDistance(const Vector2int& a, const Vector2int& b)
	{
		return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
	}

	float Math::VectorDistance(const Vector3f& a, const Vector3f& b)
	{
		return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2) + std::pow(b.z - a.z, 2));
	}

	float Math::VectorDistance(const Vector3int& a, const Vector3int& b)
	{
		return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2) + std::pow(b.z - a.z, 2));
	}

	float Math::Clamp(const float& value, const float& min, const float& max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;

		return value;
	}

	double Math::Clamp(const double& value, const double& min, const double& max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;

		return value;
	}

	int Math::Clamp(const int& value, const int& min, const int& max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;

		return value;
	}

	int Math::Lerp(const int& a, const int& b, const float& t)
	{
		return std::round(a + (b - a) * Clamp(t, 0.0f, 1.0f));
	}
	
	float Math::Lerp(const float& a, const float& b, const float& t)
	{
		return (a + (b - a) * Clamp(t, 0.0f, 1.0f));
	}

	Vector2f Math::Lerp(const Vector2f& a, const Vector2f& b, const float& t)
	{
		return Vector2f(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t));
	}

	Vector2int Math::Lerp(const Vector2int& a, const Vector2int& b, const float& t)
	{
		return Vector2int(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t));
	}

	Vector3f Math::Lerp(const Vector3f& a, const Vector3f& b, const float& t)
	{
		return Vector3f(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t), Lerp(a.z, b.z, t));
	}

	Vector3int Math::Lerp(const Vector3int& a, const Vector3int& b, const float& t)
	{
		return Vector3int(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t), Lerp(a.z, b.z, t));
	}


	float Math::CenterPoint(const float& a, const float& b)
	{
		return (a + b) / 2;
	}

	Vector2f Math::CenterPoint(const Vector2f& a, const Vector2f& b)
	{
		return Vector2f(CenterPoint(a.x, b.x), CenterPoint(a.y, b.y));
	}

	Vector2f Math::CenterPoint(const Vector2int& a, const Vector2int& b)
	{
		return Vector2f(CenterPoint(a.x, b.x), CenterPoint(a.y, b.y));
	}

	Vector3f Math::CenterPoint(const Vector3f& a, const Vector3f& b)
	{
		return Vector3f(CenterPoint(a.x, b.x), CenterPoint(a.y, b.y), CenterPoint(a.z, b.z));
	}

	Vector3f Math::CenterPoint(const Vector3int& a, const Vector3int& b)
	{
		return Vector3f(CenterPoint(a.x, b.x), CenterPoint(a.y, b.y), CenterPoint(a.z, b.z));
	}

	Vector2int Math::FindClosestPoint(const Vector2int& point, Vector2int points[], const int& pointCount)
	{
		Vector2int currentClosestPoint = points[0];
		float currentClosestDistance = VectorDistance(point, points[0]);

		for (int i = 1; i < pointCount; i++)
		{
			float distance = VectorDistance(point, points[i]);

			/* Compare the distance to the current shortest one. Also set a new closest point if the previous one 
			 * was in the exact same position */
			if (distance <= currentClosestDistance || currentClosestDistance == 0.0f)
			{
				currentClosestPoint = points[i];
				currentClosestDistance = distance;
			}
		}
		return currentClosestPoint;
	}

	Vector2int Math::FindClosestPoint(const Vector2int& point, const std::vector<Vector2int>& points)
	{
		Vector2int currentClosestPoint = points[0];
		float currentClosestDistance = VectorDistance(point, points[0]);

		for (int i = 1; i < (int)points.size(); i++)
		{
			float distance = VectorDistance(point, points[i]);

			/* Compare the distance to the current shortest one. Also set a new closest point if the previous one 
			 * was in the exact same position */
			if (distance <= currentClosestDistance || currentClosestDistance == 0.0f)
			{
				currentClosestPoint = points[i];
				currentClosestDistance = distance;
			}
		}
		return currentClosestPoint;
	}


	Vector2int Math::FindClosestPoint(const Vector2int& point, const std::vector<Vector2int>& points, const std::vector<Vector2int>& ignoredPoints)
	{
		/* Find the first non-ignored point */
		Vector2int firstNotIgnored;
		for (int i = 0; i < (int)points.size(); i++)
		{
			bool ignored = false;
			for (int j = 0; j < (int)ignoredPoints.size(); j++)
			{
				if (points[i] == ignoredPoints[j])
				{
					ignored = true;
					break;
				}
			}

			if (!ignored)
			{
				firstNotIgnored = points[i];
				break;
			}
		}

		Vector2int currentClosestPoint = firstNotIgnored;
		float currentClosestDistance = VectorDistance(point, points[0]);

		bool ignore;
		for (int i = 1; i < (int)points.size(); i++)
		{
			ignore = false;

			/* Check if the point is in the ignore list */
			for (int j = 0; j < (int)ignoredPoints.size(); j++)
				if (points[i] == ignoredPoints[j])
				{
					ignore = true;
					break;
				}

			if (!ignore)
			{
				float distance = VectorDistance(point, points[i]);

				/* Compare the distance to the current shortest one. Also set a new closest point if the previous one 
				 * was in the exact same position */
				if (distance <= currentClosestDistance || currentClosestDistance == 0.0f)
				{
					currentClosestPoint = points[i];
					currentClosestDistance = distance;
				}
			}
		}
		return currentClosestPoint;
	}

	double Math::Round(const double& value, const int& decimal_points)
	{
		/* How this thing works: 
		 * 1. Multiply the value with 10 ^ decimal points. This will leave the needed values before the decimal point
		 * 2. Round to integer
		 * 3. Divide the value with 10 ^ decimal points to get the desired rounded decimal value
		 * */
		return std::round(value * std::pow(10, decimal_points)) / std::pow(10, decimal_points);
	}

	bool Math::IsDigit(const float& value)
	{
		return ((int)value == value);
	}

	bool Math::IsDigit(const double& value)
	{
		return ((int)value == value);
	}
}
