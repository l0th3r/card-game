#include "mouse_handler.h"

#include <raylib.h>
#include <stdlib.h>

#include "DCard.h"

mouse_t* get_mouse()
{
	static mouse_t* mouse = NULL;

	if (!mouse)
	{
		mouse = malloc(sizeof(mouse_t));
		if(mouse)
		{
			mouse->x = 0;
			mouse->y = 0;
			mouse->wheel = 0;

			mouse->left = false;
			mouse->right = false;
			mouse->mid = false;

			mouse->holded = NULL;
		}
	}
	return mouse;
}

void update_mouse()
{
	mouse_t* m = get_mouse();

	m->x = GetMouseX();
	m->y = GetMouseY();
	m->wheel = GetMouseWheelMove();

	DrawText(TextFormat("x=%d y=%d", m->x, m->y), 5, 5, 10, BLACK);

	m->left = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
	m->right = IsMouseButtonPressed(MOUSE_RIGHT_BUTTON);
	m->mid = IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON);

	check_holded();
}

bool is_mouse_hovering(int x1, int y1, int x2, int y2)
{
	mouse_t* m = get_mouse();

	if ((m->x >= x1 && m->x <= x2) && (m->y >= y1 && m->y <= y2))
		return true;
	else
		return false;
}

void check_holded()
{
	mouse_t* m = get_mouse();

	if (m->holded != NULL)
	{
		m->holded->x = m->x;
		m->holded->y = m->y;
	}		
}

void dest_mouse()
{
	free(get_mouse());
}