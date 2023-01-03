#include "Circle.hpp"
#include "Particles.hpp"
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
			for (size_t i = 0; i < particles.size(); ++i)
			{
				/* Reduce the last frametime from particle life */
				particles[i].life -= timestep->deltaTime;

				/* Kill the particle if its lifetime is over */
				if (particles[i].life < 0)
				{
					particles[i].alive = false;
					continue;
				}

				/* Move the particle according to its direction */
				particles[i].pos += particles[i].direction * timestep->deltaTime;
			}

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
			

			/* Spawn new particles or re-use old ones */
			time_until_next_particle += timestep->deltaTime;
			if (time_until_next_particle > speed && spawn_new_particles)
			{
				int particle_index = -1;
				for (size_t i = 0; i < particles.size(); ++i)
				{
					if (!particles[i].alive)
					{
						particle_index = i;
					}
				}

				if (particle_index == -1)
				{
					particles.push_back(reference_particle);
					particle_index = particles.size() - 1;
				}

				particles[particle_index].pos = pos;

				// FIXME: Set a random particle direction and speed for now

				//particles[particle_index].direction.x = rand.RandomFloat(-200, 200);
				//particles[particle_index].direction.y = rand.RandomFloat(-200, 200);
				
				Vector2 next_dir = pattern->NextDirection();
				particles[particle_index].direction.x = next_dir.x * particles[particle_index].particle_speed;
				particles[particle_index].direction.y = next_dir.y * particles[particle_index].particle_speed;
				particles[particle_index].alive = true;
				particles[particle_index].life = reference_particle.life;
			}
		}

		int ParticleSource::ParticleCount() const
		{
			return particles.size();
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
			/* Move all of the particles by the delta amount */
			for (size_t i = 0; i < particles.size(); ++i)
				particles[i].pos += delta;
		}
	}
}
