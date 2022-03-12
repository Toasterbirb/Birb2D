#include "Vector.hpp"
#include "Utils.hpp"

namespace Birb
{
	std::string Vector2f::toString()
	{
		return "(" + utils::CleanDecimals(x) + ", " + utils::CleanDecimals(y) + ")";
	}

	std::string Vector2int::toString()
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	}

	std::string Vector3f::toString()
	{
		return "(" + utils::CleanDecimals(x) + ", " + utils::CleanDecimals(y) + ", " + utils::CleanDecimals(z) + ")";
	}

	std::string Vector3int::toString()
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
	}
}
