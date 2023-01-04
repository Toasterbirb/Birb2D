#include "Circle.hpp"
#include "ParticleSource.hpp"
#include "Render.hpp"
#include "Vector/Vector2.hpp"

/* Randomness source */

namespace Birb
{
	namespace Particles
	{
		ParticleSource::ParticleSource(TimeStep* timestep)
		:timestep(timestep)
		{
			type = ParticleType::Circle;
		}

		void ParticleSource::Emit(bool spawn_new_particles)
		{
			/* Find the first dead particle that we can re-use later on */
			int dead_particle_index = -1;

			for (size_t i = 0; i < particles.size(); ++i)
			{
				/* Reduce the last frametime from particle life */
				particles[i].life -= timestep->deltaTime;

				/* Kill the particle if its lifetime is over */
				if (particles[i].life < 0)
				{
					particles[i].alive = false;
					dead_particle_index = i;
					continue;
				}

				/* Move the particle according to its direction */
				particles[i].pos += particles[i].direction * timestep->deltaTime;
			}


			/* Spawn new particles or re-use old ones */
			time_until_next_particle += timestep->deltaTime;
			if (time_until_next_particle > speed && spawn_new_particles)
			{
				if (dead_particle_index == -1)
				{
					particles.push_back(reference_particle);
					dead_particle_index = particles.size() - 1;
				}

				particles[dead_particle_index].pos = pos;

				Vector2 next_dir = pattern->NextDirection();
				particles[dead_particle_index].direction.x = next_dir.x * particles[dead_particle_index].particle_speed;
				particles[dead_particle_index].direction.y = next_dir.y * particles[dead_particle_index].particle_speed;
				particles[dead_particle_index].alive = true;
				particles[dead_particle_index].life = reference_particle.life;
			}
		}

		int ParticleSource::ParticleCount() const
		{
			return particles.size();
		}

		void ParticleSource::RemoveDeadParticles()
		{
			/* Pop back any dead particles */
			if (particles.size() > 1 && particles[particles.size() - 1].alive == false)
			{
				int last_index = -1;
				for (size_t i = particles.size() - 2; i > 0; --i)
				{
					if (particles[i].alive)
					{
						last_index = i + 1;
						break;
					}
				}

				if (last_index != -1)
				{
					particles[last_index] = particles.back();
					particles.pop_back();
				}
			}
		}

		void ParticleSource::RenderFunc()
		{
			switch (type)
			{
				case (ParticleType::Pixel):
					break;

				case (ParticleType::Circle):
					for (size_t i = 0; i < particles.size(); ++i)
					{
						if (particles[i].alive)
							Render::DrawCircle(Circle(particles[i].size, particles[i].pos.ToInt(), particles[i].color));
					}
					break;

				case (ParticleType::Rect):
					break;
			}
		}

		void ParticleSource::SetPos(const Vector2& delta)
		{
			pos += delta;
		}
	}
}
