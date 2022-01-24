#pragma once
#include <vector>
#include "Entity.hpp"
#include "Renderwindow.hpp"

namespace Birb
{
	class UI
	{
	public:
		UI();
		std::vector<Entity> Buttons;
		void AddButton(Entity buttonEntity);
		void PollButtons(Window window);
	};
}
