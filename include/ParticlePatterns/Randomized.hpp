#pragma once

#include "ParticlePattern.hpp"
#include "Random.hpp"

namespace Birb
{
	namespace Particles
	{
		namespace Patterns
		{
			class Randomized : public ParticlePattern
			{
			public:
				Vector2 NextDirection() override;
			};
		}
	}
}
