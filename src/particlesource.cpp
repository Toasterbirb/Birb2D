#include "Circle.hpp"
#include "ParticleSource.hpp"
#include "Physics.hpp"
#include "Random.hpp"
#include "Render.hpp"
#include "Values.hpp"
#include "Vector/Vector2.hpp"

/* Randomness source */

namespace Birb
{
	namespace Particles
	{
		ParticleSource::ParticleSource()
		:type(ParticleType::Circle), particle_count(1), timestep(nullptr)
		{}

		ParticleSource::ParticleSource(TimeStep* timestep)
		:type(ParticleType::Circle), particle_count(1), timestep(timestep)
		{}

		void ParticleSource::Emit(bool spawn_new_particles)
		{
			/* Find the first dead particle that we can re-use later on */
			//int dead_particle_index = -1;
			dead_particles.clear();

			for (size_t i = 0; i < particles.size(); ++i)
			{
				/* Reduce the last frametime from particle life */
				particles[i].life -= timestep->deltaTime;

				/* Kill the particle if its lifetime is over */
				if (particles[i].life < 0)
				{
					particles[i].alive = false;
					dead_particles.push_back(i);
					//dead_particle_index = i;
					continue;
				}

				/* Move the particle according to its direction */
				particles[i].pos += particles[i].direction * timestep->deltaTime;

				/* Handle gravity */
				particles[i].direction.y += particles[i].gravity;

			}


			/* Spawn new particles or re-use old ones */
			time_until_next_particle += timestep->deltaTime;

			int dead_particle_index 	= 0;
			int dead_particle_counter 	= 0;

			if (dead_particles.size() == 0)
				dead_particle_index = -1;
			else
				dead_particle_index = dead_particles[0];

			if (time_until_next_particle > speed && spawn_new_particles)
			{
				time_until_next_particle = 0;
				for (int i = 0; i < particle_count; ++i)
				{
					if (dead_particle_index == -1 || dead_particle_counter > static_cast<int>(dead_particles.size() - 1))
					{
						particles.push_back(reference_particle);
						dead_particle_index = particles.size() - 1;
					}
					else
					{
						dead_particle_index = dead_particles[dead_particle_counter];
						dead_particle_counter++;
					}

					/* Pick a random position in the spawn area */
					particles[dead_particle_index].pos.x = Global::random.RandomFloat(spawn_area.x, spawn_area.x + spawn_area.w);
					particles[dead_particle_index].pos.y = Global::random.RandomFloat(spawn_area.y, spawn_area.y + spawn_area.h);


					Vector2 next_dir = pattern->NextDirection();
					particles[dead_particle_index].direction.x = next_dir.x * particles[dead_particle_index].particle_speed;
					particles[dead_particle_index].direction.y = next_dir.y * particles[dead_particle_index].particle_speed;
					particles[dead_particle_index].alive = true;
					particles[dead_particle_index].life = reference_particle.life;
				}
			}
		}

		int ParticleSource::ParticleCount() const
		{
			return particles.size();
		}

		void ParticleSource::CullParticles(const Rect& area)
		{
			for (size_t i = 0; i < particles.size(); ++i)
			{
				if (!Physics::PointInRect(area, particles[i].pos))
					particles[i].alive = false;
			}
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

		void ParticleSource::ClearParticles()
		{
			particles.clear();
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
			spawn_area.x += delta.x;
			spawn_area.y += delta.y;
		}
	}
}
