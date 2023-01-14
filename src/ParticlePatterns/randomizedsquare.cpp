#include "ParticlePatterns/RandomizedSquare.hpp"
#include "Vector/Vector2.hpp"
#include "Values.hpp"


namespace Birb
{
	namespace Particles
	{
		namespace Patterns
		{
			Vector2 RandomizedSquare::NextDirection()
			{
				return Vector2(Global::random.RandomFloat(-1, 1), Global::random.RandomFloat(-1, 1));
			}
		}
	}
}
