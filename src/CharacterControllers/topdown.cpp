#include "CharacterControllers/TopDown.hpp"
#include "Input.hpp"
#include "Values.hpp"

namespace Birb
{
	namespace CharacterController
	{
		TopDown::TopDown(float& pos_x, float& pos_y, TimeStep* timestep)
		:pos_x(pos_x), pos_y(pos_y), timestep(timestep)
		{}

		void TopDown::ProcessInput()
		{
			direction = Input::DirectionalInput();
			keydown = direction != Vector2(0, 0);
		}

		void TopDown::UpdatePosition()
		{
			if (keydown)
			{
				Vector2 delta = {
					direction.x * speed * timestep->deltaTime,
					direction.y * speed * timestep->deltaTime
				};

				/* Move the player */
				pos_x -= delta.x;
				pos_y -= delta.y;

				/* Move the camera if camera follow is enabled */
				if (camera_follow)
				{
					Global::RenderVars::CameraPosition.x -= delta.x;
					Global::RenderVars::CameraPosition.y -= delta.y;
				}
			}
		}

		Vector2 TopDown::Direction() const
		{
			return direction;
		}
	}
}
