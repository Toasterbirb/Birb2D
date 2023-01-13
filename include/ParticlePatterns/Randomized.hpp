#pragma once

#include "ParticlePattern.hpp"

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
