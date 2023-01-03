#include "ParticlePatterns/Randomized.hpp"
#include "Vector/Vector2.hpp"


namespace Birb
{
	namespace Particles
	{
		namespace Patterns
		{
			Vector2 Randomized::NextDirection()
			{
				return Vector2(rand.RandomFloat(-1, 1), rand.RandomFloat(-1, 1));
			}
		}
	}
}
