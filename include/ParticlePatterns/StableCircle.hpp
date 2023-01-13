#pragma once

#include "ParticlePattern.hpp"
#include "Circle.hpp"

namespace Birb
{
	namespace Particles
	{
		namespace Patterns
		{
			class StableCircle : public ParticlePattern
			{
			public:
				StableCircle();
				Vector2 NextDirection() override;

			private:
				Circle circle;
			};
		}
	}
}
