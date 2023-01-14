#include "Values.hpp"
#include "ParticlePatterns.hpp"
#include "Color.hpp"
#include "ParticleSource.hpp"
#include "Scene.hpp"
#include "Timer.hpp"
#include "Game.hpp"
#include "doctest.h"
#include <iostream>
#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace Birb;

namespace BirbTest
{
	void particles_start(Game& game);
	void particles_input(Game& game);
	void particles_update(Game& game);
	void particles_fixed_update();
	void particles_render(Game& game);
	void particles_post_render();
	void particles_cleanup();

	Timer timer;
	Particles::Patterns::RandomizedSquare	particle_pattern;
	Particles::Patterns::RandomizedCircle 	randomized_circle(0.5f);
	Particles::Patterns::StableCircle 		stable_circle;
	Particles::Patterns::StableSquare 		stable_square;
	Particles::Patterns::Spiral 			spiral(20.0f);
	Particles::ParticleSource* ps;
	Scene main_scene;

	Rect viewport_area(0, 0, 1280, 720);

	float effect_duration = 1.0f;
	int effect_counter = 0;
	static constexpr int effect_count = 8;

	TEST_CASE("Rendering: Simple particle effect")
	{
		Game::WindowOpts win_opts;
		win_opts.refresh_rate = 240;
		win_opts.title = "Birb2D particle system test";
		Game game(win_opts, particles_start, particles_input, particles_update, particles_render);
		game.post_render = particles_post_render;
		game.fixed_update = particles_fixed_update;
		game.cleanup = particles_cleanup;

		game.Start();
	}

	void particles_start(Game& game)
	{
		timer.Start();
		ps = new Particles::ParticleSource(game.time_step());
		main_scene.AddObject(ps);

		ps->spawn_area.x = game.window->dimensions.x / 2.0f;
		ps->spawn_area.y = game.window->dimensions.y / 2.0f;
		ps->spawn_area.color = Colors::Nord::PolarNight::nord0;

		ps->reference_particle.color = Colors::White;
		ps->reference_particle.life = 1.3f;
		ps->reference_particle.particle_speed = 200.0f;
		ps->speed = 0.01;
		ps->pattern = &particle_pattern;
	}

	void particles_input(Game& game)
	{

	}

	void particles_update(Game& game)
	{
		if (timer.ElapsedSeconds() < effect_duration)
		{
			/* If we are demoing the spiral pattern, randomize
			 * the particle colors */
			if (effect_counter == effect_count - 1)
				ps->reference_particle.color = Color(Global::random.RandomInt(0, 255), Global::random.RandomInt(0, 255), Global::random.RandomInt(0, 255));

			ps->Emit(true);
		}
		else if (timer.ElapsedSeconds() > effect_duration + 0.5f)
		{
			effect_counter++;
			timer.Start();

			/* Clear the particles */
			ps->ClearParticles();

			switch (effect_counter)
			{
				case (1):
				{
					ps->spawn_area.x -= 20;
					ps->spawn_area.y -= 20;
					ps->spawn_area.w += 40;
					ps->spawn_area.h += 40;
					break;
				}

				case (2):
				{
					ps->spawn_area.x += 20;
					ps->spawn_area.y += 20;
					ps->spawn_area.w -= 40;
					ps->spawn_area.h -= 40;

					ps->reference_particle.particle_speed = 300;
					ps->reference_particle.gravity = 5.0f;
					ps->reference_particle.life = 4.0f;
					break;
				}

				case (3):
				{
					ps->particle_count = 400;
					ps->speed = 0.5f;
					ps->reference_particle.gravity = 1.0f;
					effect_duration = 0.3f;
					break;
				}

				case (4):
				{
					ps->pattern = &randomized_circle;
					break;
				}

				case (5):
				{
					ps->pattern = &stable_circle;
					break;
				}

				case (6):
				{
					ps->pattern = &stable_square;
					break;
				}

				case (7):
				{
					ps->pattern = &spiral;
					ps->speed = 0.02f;
					ps->particle_count = 1;
					effect_duration = 2.0f;
					break;
				}
			}
		}
		else
			ps->Emit(false);

		if (effect_counter > effect_count - 1)
			game.application_running = false;

		std::cout << "\rParticle count: " << ps->ParticleCount() << "\t";
	}

	void particles_fixed_update()
	{
		ps->CullParticles(viewport_area);
		ps->RemoveDeadParticles();
	}

	void particles_render(Game& game)
	{
		Render::DrawRect(ps->spawn_area);
		main_scene.Render();
	}

	void particles_post_render()
	{

	}

	void particles_cleanup()
	{
		std::cout << "\n";
	}
}
