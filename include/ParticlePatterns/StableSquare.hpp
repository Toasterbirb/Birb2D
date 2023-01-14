#pragma once

#include "ParticlePattern.hpp"

namespace Birb
{
	namespace Particles
	{
		namespace Patterns
		{
			class StableSquare : public ParticlePattern
			{
			public:
				Vector2 NextDirection() override;
			};
		}
	}
}
