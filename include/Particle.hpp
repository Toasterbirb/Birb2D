#pragma once

#include "Color.hpp"
#include "Vector/Vector2.hpp"

namespace Birb
{
	namespace Particles
	{
		struct Particle
		{
			/// How long until the particle is going to "die"
			float life = 0.2f;

			/// Controls the size of the particles. The way this
			/// variable behaves depends a lot on the particle type.
			/// For example, this variable won't change anything with
			/// pixel particles
			float size = 2.0f;

			/// Multiplier for the particle direction
			float particle_speed = 200.0f;

			Color color;

			/// Absolute position of the particle on-screen
			Vector2 pos;

			/// The speed and direction of the particle
			Vector2 direction;

			/// Particle weight
			float gravity = 0;

			/// If the particle is dead, it won't be rendered.
			bool alive = true;
		};
	}
}
