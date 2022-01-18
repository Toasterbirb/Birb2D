#pragma once
#include <iostream>
#include <math.h>

namespace Birb
{
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

		float x, y;
	};

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

		int x, y;
	};

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

		float x, y, z;
	};

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

		int x, y, z;
	};
}
