#pragma once
#include <iostream>
#include <math.h>


struct Vector2f
{
	Vector2f()
	:x(0.0f), y(0.0f)
	{}

	Vector2f(float p_x, float p_y)
	:x(p_x), y(p_y)
	{}

	void print()
	{
		std::cout << x << ", " << y << std::endl;
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

	void print()
	{
		std::cout << x << ", " << y << std::endl;
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

	void print()
	{
		std::cout << x << ", " << y << ", " << z << std::endl;
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

	void print()
	{
		std::cout << x << ", " << y << ", " << z << std::endl;
	}

	int x, y, z;
};
