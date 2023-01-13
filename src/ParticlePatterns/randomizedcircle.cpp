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
			RandomizedCircle::RandomizedCircle()
			:circle(1, Vector2Int(0, 0))
			{}

			Vector2 RandomizedCircle::NextDirection()
			{
				return Math::FindPointOnCircle(circle, Global::random.RandomFloat(0, 360));
			}
		}
	}
}
