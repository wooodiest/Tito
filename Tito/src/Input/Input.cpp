#include "Input.h"

void Input::Listen()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Engine::GetInstance().Quit();
			break;
		case SDL_KEYDOWN:
			GetKeyBoardSates();
			break;
		case SDL_KEYUP:
			GetKeyBoardSates();
			break;
		case SDL_MOUSEWHEEL:
			if (event.wheel.y > 0) /// mouse wheel up
			{
				if (DISPLAY_SCALE >= 1)
					DISPLAY_SCALE += DISPLAY_SCALE_STEP * 10;
				else
					DISPLAY_SCALE += DISPLAY_SCALE_STEP;

				if (DISPLAY_SCALE > DISPLAY_SCALE_MAX)
					DISPLAY_SCALE = DISPLAY_SCALE_MAX;
			}
			else if (event.wheel.y < 0) /// mouse wheel down
			{
				if (DISPLAY_SCALE > 1)
					DISPLAY_SCALE -= DISPLAY_SCALE_STEP * 10;
				else
					DISPLAY_SCALE -= DISPLAY_SCALE_STEP;

				if (DISPLAY_SCALE < DISPLAY_SCALE_MIN)
					DISPLAY_SCALE = DISPLAY_SCALE_MIN;
			}

		default:
			break;
		}
	}
}

bool Input::GetKeyDown(SDL_Scancode key) const
{
	return m_KeyStates[key] == 1;
}
