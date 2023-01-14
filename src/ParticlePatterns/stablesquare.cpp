#include "ParticlePatterns/StableSquare.hpp"
#include "Vector/Vector2.hpp"
#include "Values.hpp"


namespace Birb
{
	namespace Particles
	{
		namespace Patterns
		{
			Vector2 StableSquare::NextDirection()
			{
				/* First decide on a side */
				int side = Global::random.RandomInt(0, 3);

				switch (side)
				{
					case (0):
					{
						return Vector2(Global::random.RandomFloat(-1, 1), -1);
						break;
					}

					case (1):
					{
						return Vector2(Global::random.RandomFloat(-1, 1), 1);
						break;
					}

					case (2):
					{
						return Vector2(-1, Global::random.RandomFloat(-1, 1));
						break;
					}

					case (3):
					{
						return Vector2(1, Global::random.RandomFloat(-1, 1));
						break;
					}

					default:
					{
						return Vector2(Global::random.RandomFloat(-1, 1), Global::random.RandomFloat(-1, 1));
						break;
					}
				}
			}
		}
	}
}
