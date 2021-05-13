#include "mouse_handler.h"

#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>

#include "DCard.h"

/*DrawText(TextFormat("x=%0.f y=%0.f", m->holded->x, m->holded->y), 5, 5, 10, BLACK);*/

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

	m->left = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
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

void give_card(Vector2* coord)
{
	mouse_t* m = get_mouse();

	if (!m->holded)
		m->holded = coord;
}

void check_holded()
{
	mouse_t* m = get_mouse();

	if (m->holded != NULL)
	{
		m->holded->x = m->x;
		m->holded->y = m->y;

		if (m->left)
			m->holded = NULL;
	}
}

void dest_mouse()
{
	free(get_mouse());
}