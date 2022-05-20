#include "Vector.hpp"
#include "Utils.hpp"

namespace Birb
{
	std::string Vector2f::toString() const
	{
		return "(" + utils::CleanDecimals(x) + ", " + utils::CleanDecimals(y) + ")";
	}

	Vector2int Vector2f::toInt() const
	{
		return Vector2int(std::round(x), std::round(y));
	}

	std::string Vector2int::toString() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	}

	Vector2f Vector2int::toFloat() const
	{
		return Vector2f(x, y);
	}

	std::string Vector3f::toString() const
	{
		return "(" + utils::CleanDecimals(x) + ", " + utils::CleanDecimals(y) + ", " + utils::CleanDecimals(z) + ")";
	}

	Vector3int Vector3f::toInt() const
	{
		return Vector3int(std::round(x), std::round(y), std::round(z));
	}

	std::string Vector3int::toString() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
	}

	Vector3f Vector3int::toFloat() const
	{
		return Vector3f(x, y, z);
	}
}
