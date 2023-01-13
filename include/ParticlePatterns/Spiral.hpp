#pragma once

#include "ParticlePattern.hpp"
#include "Circle.hpp"

namespace Birb
{
	namespace Particles
	{
		namespace Patterns
		{
			class Spiral : public ParticlePattern
			{
			public:
				Spiral(float speed);
				Vector2 NextDirection() override;
				float speed; ///< Controls how quickly the patterns will go around

			private:
				Circle circle;
				float accumulator;
			};
		}
	}
}
