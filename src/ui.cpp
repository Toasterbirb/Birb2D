#include "UI.hpp"

namespace Birb
{
	UI::UI() {}

	void UI::AddButton(Entity* buttonEntity)
	{
		Buttons.push_back(buttonEntity);
	}

	void UI::PollButtons(const Window& window) const
	{
		for (int i = 0; i < (int)Buttons.size(); i++)
		{
			/* Skip inactive buttons */
			if (!Buttons[i]->clickComponent.active)
				continue;

			/* Skip buttons that are in an inactive scene */
			if (Buttons[i]->sceneActive == false)
				continue;

			/* Check if the cursor is on top of the button */
			if (!window.CursorInRect(Buttons[i]->rect))
				continue;

			/* Run the button click event if there was a mouseclick */
			if (window.event.type == SDL_MOUSEBUTTONDOWN)
				Buttons[i]->clickComponent.onClick();

			/* You can really only click one button at once, so lets stop if we got this far */
			break;
		}
	}
}
