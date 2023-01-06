#include "ParticlePatterns/Randomized.hpp"
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
	void particles_render(Game& game);
	void particles_post_render();
	void particles_cleanup();

	Timer timer;
	Particles::Patterns::Randomized particle_pattern;
	Particles::ParticleSource* ps;
	Scene main_scene;

	TEST_CASE("Rendering: Simple particle effect")
	{
		Game::WindowOpts win_opts;
		win_opts.refresh_rate = 240;
		win_opts.title = "Birb2D particle system test";
		Game game(win_opts, particles_start, particles_input, particles_update, particles_render);
		game.post_render = particles_post_render;
		game.cleanup = particles_cleanup;

		game.Start();
	}

	void particles_start(Game& game)
	{
		timer.Start();
		ps = new Particles::ParticleSource(game.time_step());
		main_scene.AddObject(ps);

		ps->pos.x = game.window->dimensions.x / 2.0f;
		ps->pos.y = game.window->dimensions.y / 2.0f;

		ps->reference_particle.color = Colors::White;
		ps->reference_particle.life = 1.3f;
		ps->reference_particle.particle_speed = 200.0f;
		ps->speed = 0.5;
		ps->pattern = &particle_pattern;
	}

	void particles_input(Game& game)
	{

	}

	void particles_update(Game& game)
	{
		if (timer.ElapsedSeconds() < 1.0f)
			ps->Emit(true);
		else if (timer.ElapsedSeconds() > 2.0f)
			game.application_running = false;
		else
			ps->Emit(false);

		std::cout << "\rParticle count: " << ps->ParticleCount() << "\t";
	}

	void particles_render(Game& game)
	{
		main_scene.Render();
	}

	void particles_post_render()
	{
		ps->RemoveDeadParticles();
	}

	void particles_cleanup()
	{
		std::cout << "\n";
	}
}
