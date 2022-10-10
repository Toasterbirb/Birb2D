#include <random>
#include "Random.hpp"

namespace Birb
{
	Random::Random()
	{
		srand(time(0));
	}

	int Random::RandomInt(const int& min, const int& max)
	{
		if (max < min)
			return min;

		return rand() % (max + 1 - min) + min;
	}

	float Random::RandomFloat(const float& min, const float& max)
	{
		if (max < min)
			return min;

		float random = (static_cast<float> (rand())) / static_cast<float> (RAND_MAX);
		float range = max - min;
		return (random * range) + min;
	}
}
