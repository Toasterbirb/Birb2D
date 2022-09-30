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

		/* Sort the button entity pointers by their rendering priority
		 * if there are more than 2 buttons in the UI object */
		SortButtons();
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

		/* Find all active buttons that are in active scenes */
		std::vector<Entity*> active_buttons;
		for (size_t i = 0; i < Buttons.size(); ++i)
		{
			/* Skip inactive buttons */
			if (!Buttons[i]->clickComponent.active)
				continue;

			/* Skip buttons that are in an inactive scene */
			if (Buttons[i]->sceneActive == false)
				continue;

			active_buttons.push_back(Buttons[i]);
		}

		/* Handle the moouse clicky clicky stuff */
		for (size_t i = 0; i < active_buttons.size(); ++i)
		{
			/* Check if the cursor is on top of the button */
            if (window.CursorInRect(active_buttons[i]->rect))
                Buttons[i]->clickComponent.onHover();
            else
                continue;

            /* Check if we are dragging */
			if (window.event.type != SDL_MOUSEBUTTONDOWN && window.event.type != SDL_MOUSEBUTTONUP && mouseHeldDown)
            {
                active_buttons[i]->clickComponent.onDrag();
                continue; /* It is impossible to click and drag at the same time */
            }
			else if (window.event.type == SDL_MOUSEBUTTONDOWN)
			{
				active_buttons[i]->clickComponent.onMouseDown();
				active_buttons[i]->clickComponent.isPressed = true;
				continue;
			}

            /* Check if the mousebutton is released */
            if (window.event.type == SDL_MOUSEBUTTONUP)
			{
                active_buttons[i]->clickComponent.onClick();
				active_buttons[i]->clickComponent.isPressed = false;
			}

			/* You can really only click one button at once, so lets stop if we got this far */
			break;
		}
	}

	void UI::SortButtons()
	{
		if (Buttons.size() > 1)
		{
			Entity* tmpObject;
			int j;
			for (size_t i = 1; i < Buttons.size(); ++i)
			{
				tmpObject = Buttons[i];
				j = i - 1;

				/* The object rendered last is going to be the first one,
				 * so this sorting algo needs to be the reverse of the sceneobject
				 * sorting algo */
				while (j >= 0 && Buttons[j]->renderingPriority < tmpObject->renderingPriority)
				{
					Buttons[j + 1] = Buttons[j];
					j = j - 1;
				}
				Buttons[j + 1] = tmpObject;
			}
		}
	}
}
