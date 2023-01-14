#pragma once

#include "ParticlePattern.hpp"

namespace Birb
{
	namespace Particles
	{
		namespace Patterns
		{
			class RandomizedSquare : public ParticlePattern
			{
			public:
				Vector2 NextDirection() override;

			private:
				float randomness_control;
			};
		}
	}
}
