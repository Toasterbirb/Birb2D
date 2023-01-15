#pragma once

#ifndef DISTCC
#include "STD.hpp"
#else
#include <vector>
#endif

#include "Entities/Button.hpp"
#include "Renderwindow.hpp"

namespace Birb
{
	class UI
	{
	public:
		UI();
		std::vector<Entity::Button*> Buttons;
		void AddButton(Entity::Button* buttonEntity); ///< Addin't an entity to this list makes it interactable as a button
		void PollButtons(const Window& window); ///< Check if the user is clicking on any buttons etc.
		void SortButtons(); ///< Sort buttons by their rendering priority

    private:
        bool mouseHeldDown;
	};
}
