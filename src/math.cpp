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

		Vector2f Math::CenterPoint(Vector2f a, Vector2f b)
		{
			return Vector2f((a.x + b.x) / 2, (a.y + b.y) / 2);
		}

		Vector2f Math::CenterPoint(Vector2int a, Vector2int b)
		{
			return Vector2f((a.x + b.x) / 2.0f, (a.y + b.y) / 2.0f);
		}

		Vector3f Math::CenterPoint(Vector3f a, Vector3f b)
		{
			return Vector3f((a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2);
		}

		Vector3f Math::CenterPoint(Vector3int a, Vector3int b)
		{
			return Vector3f((a.x + b.x) / 2.0f, (a.y + b.y) / 2.0f, (a.z + b.z) / 2.0f);
		}
}
