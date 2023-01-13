#include "Math.hpp"
#include "ParticlePatterns/Spiral.hpp"
#include "Values.hpp"
#include "Vector/Vector2.hpp"


namespace Birb
{
	namespace Particles
	{
		namespace Patterns
		{
			Spiral::Spiral(float speed)
			:speed(speed), circle(1, Vector2Int(0, 0)), accumulator(0)
			{}

			Vector2 Spiral::NextDirection()
			{
				return Math::FindPointOnCircle(circle, accumulator += speed);
			}
		}
	}
}
