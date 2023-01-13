#include "Math.hpp"
#include "ParticlePatterns/StableCircle.hpp"
#include "Values.hpp"
#include "Vector/Vector2.hpp"


namespace Birb
{
	namespace Particles
	{
		namespace Patterns
		{
			StableCircle::StableCircle()
			:circle(1, Vector2Int(0, 0))
			{}

			Vector2 StableCircle::NextDirection()
			{
				return Math::FindPointOnCircle(circle, Global::random.RandomFloat(0, 360));
			}
		}
	}
}
