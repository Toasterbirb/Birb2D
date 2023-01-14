#pragma once

#include "ParticlePattern.hpp"
#include "Circle.hpp"

namespace Birb
{
	namespace Particles
	{
		namespace Patterns
		{
			class RandomizedCircle : public ParticlePattern
			{
			public:
				RandomizedCircle(float randomness_control = 0.0f);
				Vector2 NextDirection() override;

			private:
				float randomness_control;
				Circle circle;
			};
		}
	}
}
