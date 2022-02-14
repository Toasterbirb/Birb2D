#include "Math.hpp"

namespace Birb
{
	float Math::VectorDistance(Vector2f a, Vector2f b)
	{
		return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
	}

	float Math::VectorDistance(Vector2int a, Vector2int b)
	{
		return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
	}

	float Math::VectorDistance(Vector3f a, Vector3f b)
	{
		return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2) + std::pow(b.z - a.z, 2));
	}

	float Math::VectorDistance(Vector3int a, Vector3int b)
	{
		return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2) + std::pow(b.z - a.z, 2));
	}

	float Math::Clamp(float value, float min, float max)
	{
		if (value < min)
			value = min;
		else if (value > max)
			value = max;

		return value;
	}

	int Math::Clamp(int value, int min, int max)
	{
		if (value < min)
			value = min;
		else if (value > max)
			value = max;

		return value;
	}

	int Math::Lerp(int a, int b, float t)
	{
		t = Clamp(t, 0.0, 1.0f);
		return std::round(a + (b - a) * t);
	}
	
	float Math::Lerp(float a, float b, float t)
	{
		t = Clamp(t, 0.0, 1.0f);
		return (a + (b - a) * t);
	}

	Vector2f Math::Lerp(Vector2f a, Vector2f b, float t)
	{
		return Vector2f(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t));
	}

	Vector2int Math::Lerp(Vector2int a, Vector2int b, float t)
	{
		return Vector2int(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t));
	}

	Vector3f Math::Lerp(Vector3f a, Vector3f b, float t)
	{
		return Vector3f(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t), Lerp(a.z, b.z, t));
	}

	Vector3int Math::Lerp(Vector3int a, Vector3int b, float t)
	{
		return Vector3int(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t), Lerp(a.z, b.z, t));
	}


	float Math::CenterPoint(float a, float b)
	{
		return (a + b) / 2;
	}

	Vector2f Math::CenterPoint(Vector2f a, Vector2f b)
	{
		return Vector2f(CenterPoint(a.x, b.x), CenterPoint(a.y, b.y));
	}

	Vector2f Math::CenterPoint(Vector2int a, Vector2int b)
	{
		return Vector2f(CenterPoint(a.x, b.x), CenterPoint(a.y, b.y));
	}

	Vector3f Math::CenterPoint(Vector3f a, Vector3f b)
	{
		return Vector3f(CenterPoint(a.x, b.x), CenterPoint(a.y, b.y), CenterPoint(a.z, b.z));
	}

	Vector3f Math::CenterPoint(Vector3int a, Vector3int b)
	{
		return Vector3f(CenterPoint(a.x, b.x), CenterPoint(a.y, b.y), CenterPoint(a.z, b.z));
	}

	Vector2int Math::FindClosestPoint(Vector2int point, Vector2int points[], int pointCount)
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

	Vector2int Math::FindClosestPoint(Vector2int point, std::vector<Vector2int> points)
	{
		Vector2int currentClosestPoint = points[0];
		float currentClosestDistance = VectorDistance(point, points[0]);

		for (int i = 1; i < points.size(); i++)
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

	Vector2int Math::FindClosestPoint(Vector2int point, std::vector<Vector2int> points, std::vector<Vector2int> ignoredPoints)
	{
		Vector2int currentClosestPoint = points[0];
		float currentClosestDistance = VectorDistance(point, points[0]);

		bool ignore;
		for (int i = 1; i < points.size(); i++)
		{
			ignore = false;

			/* Check if the point is in the ignore list */
			for (int j = 0; j < ignoredPoints.size(); j++)
				if (points[i] == ignoredPoints[j])
					ignore = true;

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
}
