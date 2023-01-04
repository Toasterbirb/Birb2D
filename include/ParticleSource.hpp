#pragma once

#include "Color.hpp"
#include "Particle.hpp"
#include "ParticlePattern.hpp"
#include "Random.hpp"
#include "STD.hpp"
#include "SceneObject.hpp"
#include "Timestep.hpp"
#include "Vector/Vector2.hpp"

namespace Birb
{
	namespace Particles
	{
		/// Particle shape
		enum struct ParticleType
		{
			Pixel, Circle, Rect
		};

		class ParticleSource : public SceneObject
		{
		public:
			ParticleSource(TimeStep* timestep);

			float speed = 0.05f; ///< The duration in seconds between spawning each particle

			ParticleType type;
			Particle reference_particle;

			ParticlePattern* pattern;

			/// Emit particles. This function should be run every
			/// frame in the gameloop whenever you want particles to
			/// spawn
			void Emit(bool spawn_new_particles = true);

			int ParticleCount() const;

			/// Absolute position where all of the particles will be spawned from
			Vector2 pos;

			/// Pops off dead particles at the end of the particle list
			void RemoveDeadParticles();

		private:
			TimeStep* timestep;
			std::vector<Particle> particles;

			float time_until_next_particle = 0.0f;

			Random rand;

			/* SceneObject stuff */
			void RenderFunc() override;
			void SetPos(const Vector2& delta) override;
		};
	}
}
