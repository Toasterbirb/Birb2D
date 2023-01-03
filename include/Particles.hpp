#pragma once

#include "Color.hpp"
#include "ParticlePattern.hpp"
#include "Random.hpp"
#include "SceneObject.hpp"
#include "Timestep.hpp"
#include "Vector/Vector2.hpp"
#include "STD.hpp"

namespace Birb
{
	namespace Particles
	{
		/// Particle shape
		enum struct ParticleType
		{
			Pixel, Circle, Rect
		};

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

			/// If the particle is dead, it won't be rendered.
			bool alive = true;
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
