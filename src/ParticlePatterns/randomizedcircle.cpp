#include "Math.hpp"
#include "ParticlePatterns/RandomizedCircle.hpp"
#include "Values.hpp"
#include "Vector/Vector2.hpp"


namespace Birb
{
	namespace Particles
	{
		namespace Patterns
		{
			RandomizedCircle::RandomizedCircle(float randomness_control)
			:randomness_control(randomness_control), circle(1, Vector2Int(0, 0))
			{}

			Vector2 RandomizedCircle::NextDirection()
			{
				return Math::FindPointOnCircle(circle, Global::random.RandomFloat(0, 360)) * Global::random.RandomFloat(randomness_control, 1);
			}
		}
	}
}
