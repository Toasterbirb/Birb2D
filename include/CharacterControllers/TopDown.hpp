#pragma once
#include "SDL.hpp"
#include "Timestep.hpp"
#include "Vector/Vector2.hpp"

namespace Birb
{
	namespace CharacterController
	{
		class TopDown
		{
		public:
			/// @brief 		Basic top-down character controller for 2D games
			/// @param[in] 	pos_x 	Reference to the character x-position
			/// @param[in] 	pos_y 	Reference to the character y-position
			TopDown(float& pos_x, float& pos_y, TimeStep* timestep);

			/// Process keyboard input events.
			/// Call in the input() game method
			void ProcessInput();

			/// Move the player according to the inputs
			/// Call in the update() game method
			void UpdatePosition();

			/// Move the main camera with the player
			bool camera_follow = true;

			/// Player speed multiplier
			float speed = 200;

			/// Get the current direction that the player
			/// is moving to
			Vector2 Direction() const;

		private:
			float& pos_x;
			float& pos_y;
			TimeStep* timestep;

			Vector2 direction;
			bool keydown;
		};
	}
}
