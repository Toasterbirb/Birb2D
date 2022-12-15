#include "Random.hpp"

namespace Birb
{
	int Random::RandomInt(const int& min, const int& max)
	{
		if (max < min)
			return min;

		return random_machine() % (max + 1 - min) + min;
	}

	float Random::RandomFloat(const float& min, const float& max)
	{
		if (max < min)
			return min;

		float random = (static_cast<float> (random_machine())) / random_machine.max();
		float range = max - min;
		return (random * range) + min;
	}
}
