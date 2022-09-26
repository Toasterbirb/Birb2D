#include "UI.hpp"

namespace Birb
{
	UI::UI()
    {
        mouseHeldDown = false;
    }

	void UI::AddButton(Entity* buttonEntity)
	{
		Buttons.push_back(buttonEntity);
	}

	void UI::PollButtons(const Window& window)
	{
        /* Set the mouse down state */
        switch (window.event.type)
        {
            case (SDL_MOUSEBUTTONDOWN):
                mouseHeldDown = true;
                break;

            case (SDL_MOUSEBUTTONUP):
                mouseHeldDown = false;
                break;
        }

		for (size_t i = 0; i < Buttons.size(); i++)
		{
			/* Skip inactive buttons */
			if (!Buttons[i]->clickComponent.active)
				continue;

			/* Skip buttons that are in an inactive scene */
			if (Buttons[i]->sceneActive == false)
				continue;

			/* Check if the cursor is on top of the button */
            if (window.CursorInRect(Buttons[i]->rect))
                Buttons[i]->clickComponent.onHover();
            else
                continue;

            /* Check if we are dragging */
			if (window.event.type != SDL_MOUSEBUTTONDOWN && window.event.type != SDL_MOUSEBUTTONUP && mouseHeldDown)
            {
                Buttons[i]->clickComponent.onDrag();
                continue; /* It is impossible to click and drag at the same time */
            }
			else if (window.event.type == SDL_MOUSEBUTTONDOWN)
			{
				Buttons[i]->clickComponent.onMouseDown();
				continue;
			}

            /* Check if the mousebutton is released */
            if (window.event.type == SDL_MOUSEBUTTONUP)
                Buttons[i]->clickComponent.onClick();

			/* You can really only click one button at once, so lets stop if we got this far */
			break;
		}
	}
}
