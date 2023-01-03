#pragma once

#include "Vector/Vector2.hpp"

namespace Birb
{
	namespace Particles
	{
		class ParticlePattern
		{
		public:
			virtual Vector2 NextDirection() = 0;
		};
	}
}
