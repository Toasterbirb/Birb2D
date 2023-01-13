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
				RandomizedCircle();
				Vector2 NextDirection() override;

			private:
				Circle circle;
			};
		}
	}
}
